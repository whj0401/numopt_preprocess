import json
import sys

postfix_node = '.expr.paths'
postfix_json = '.json'
postfix_output = '.pth'

dir = './'

type_transform_map = {"iRRAM__scope__class_REAL": "decimal", "i": "integer", "d": "decimal", "b": "bool"}


def transform_var_type(variables):
    for var_name in variables.keys():
        variables[var_name] = type_transform_map[variables[var_name]]
    return variables


def read_json(file_name):
    file_name = dir + file_name
    file = open(file_name, "r")
    return json.load(file)


def handle_loop_json(loop, loop_name):
    loop_body = read_json(loop_name + postfix_node)
    loop['variables'] = transform_var_type(loop['variables'])
    loop['loop_body'] = handle_paths_json(loop_body)
    # there are some differences compared to walker's pth file
    # use a python script transform to pth for walker's expression optimization
    return loop


def handle_path_json(path):
    if path['constraint'] == '':
        path['constraint'] = 'true'
    content = path['path'][0]["content"]
    new_content = []
    loop = {}
    next_root_node = []
    do_break = False
    do_continue = False
    for procedure in content:
        if procedure[0].startswith('loop'):
            loop_name = procedure[0]
            loop = read_json(loop_name + '.json')
            loop = handle_loop_json(loop, loop_name)
        elif procedure[0].startswith('node'):
            node_name = procedure[0]
            next_root_node = read_json(node_name + postfix_node)
            next_root_node = handle_paths_json(next_root_node)
        elif procedure[0] == '__break__':
            do_break = True
        elif procedure[0] == '__continue__':
            do_continue = True
        else:
            new_content.append(procedure)
    path['path'][0]['content'] = new_content
    if len(loop) > 0:
        path['path'].append(loop)
    if len(next_root_node) > 0:
        if len(next_root_node) == 1:
            # to make it compatible with old solution
            path['path'].append(next_root_node[0])
        else:
            path['next_paths'] = next_root_node
    if do_break:
        path['break'] = 'true'
    else:
        path['break'] = 'false'
    if do_continue:
        path['continue'] = 'true'
    else:
        path['continue'] = 'false'
    return path


def handle_paths_json(paths):
    new_paths = []
    for path in paths:
        new_path = handle_path_json(path)
        new_paths.append(new_path)
    return new_paths


def handle_function_json(func):
    func_name = func['function_name']
    paths = read_json(func_name + postfix_node)
    func['paths'] = handle_paths_json(paths)
    # add __return__ variable to function variables table
    func['variables']['__return__'] = 'iRRAM__scope__class_REAL'
    func['variables'] = transform_var_type(func['variables'])
    return func


if __name__ == "__main__":
    file_name = sys.argv[1]
    func_json = read_json(file_name)
    new_func = handle_function_json(func_json)
    output_file = open(file_name + postfix_output, 'w')
    json.dump(new_func, output_file, indent=4)
