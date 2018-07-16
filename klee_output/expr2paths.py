import json
import sys


def expr2paths(file):
    reading_constraint = False
    reading_procedure = False
    constraint_procedure = {}
    cur_constraint = ""
    cur_procedures = []
    for line in file:
        if line == '\n':
            continue
        if line.startswith('-------'):
            if cur_constraint in constraint_procedure:
                for procedure in cur_procedures:
                    constraint_procedure[cur_constraint].append(procedure)
            else:
                constraint_procedure[cur_constraint] = cur_procedures
            cur_constraint = ""
            cur_procedures = []
            reading_constraint = False
            reading_procedure = False
            continue
        line = line.strip()
        if line.startswith('constraint'):
            reading_constraint = True
            cur_constraint = line.split('[')[1]
            if line.endswith(']'):
                cur_constraint = cur_constraint.split(']')[0]
                reading_constraint = False
                reading_procedure = True
        elif reading_constraint:
            if line.endswith(']'):
                cur_constraint += " && " + line.split(']')[0]
                reading_constraint = False
                reading_procedure = True
            else:
                cur_constraint += " && " + line
        elif reading_procedure:
            single_procedure = line.split(' = ')
            cur_procedures.append(single_procedure)
    # reform constraint_procedure to paths
    paths = []
    for key in constraint_procedure.keys():
        path = {}
        path['constraint'] = key
        path['path'] = []
        path['path'].append({'type': 'procedure', 'content': constraint_procedure[key]})
        paths.append(path)
    return paths


if __name__ == "__main__":
    file_self = True
    for file_name in sys.argv:
        if file_self:
            file_self = False
            continue
        f = open(file_name, "r")
        out = open(file_name + ".paths", "w")
        json.dump(expr2paths(f), out, indent=4)
