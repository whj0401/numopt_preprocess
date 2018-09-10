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
    loop['content']['variables'] = transform_var_type(loop['content']['variables'])
    loop['content']['loop_body'] = handle_paths_json(loop_body)
    return loop


def remove_out_layer_whole_expr_brace(expr):
    if expr[0] == '(' and expr[-1] == ')':
        brace_layer = 0
        for i in range(len(expr)):
            if expr[i] == '(':
                brace_layer += 1
            elif expr[i] == ')':
                brace_layer -= 1
            if brace_layer == 0:
                if i == len(expr) - 1:
                    return expr[1:len(expr) - 1]
                else:
                    return expr
    return expr


def handle_path_json(path):
    if path['constraint'] == '':
        path['constraint'] = 'true'
    path['constraint'] = path['constraint'].replace(' ', '')  # remove all space
    path['constraint'] = remove_out_layer_whole_expr_brace(path['constraint'])
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
            procedure[1] = remove_out_layer_whole_expr_brace(procedure[1])
            new_content.append(procedure)
    path['path'][0]['content'] = new_content
    if len(loop) > 0:
        path['path'].append(loop)
    if len(next_root_node) > 0:
        if len(next_root_node) == 1 and next_root_node[0]['constraint'] == 'true':
            # to make it compatible with old solution
            for p in next_root_node[0]['path']:
                path['path'].append(p)
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
    if len(new_content) == 0 and len(loop) == 0 and len(next_root_node) == 0:
        path['path'] = []
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


def get_program_name(func):
    src_file_name = func['program_name'].split('/')[-1]
    postfix_offset = 0
    if src_file_name.endswith('.cpp'):
        postfix_offset = 4
    elif src_file_name.endswith('.cc'):
        postfix_offset = 3
    elif src_file_name.endswith('.c') or src_file_name.endswith('.h'):
        postfix_offset = 2
    return src_file_name[:-postfix_offset]


def simplify_return_procedure(func):
    if len(func['paths']) == 1:
        p = func['paths'][0]['path']
        if len(p) > 0 and p[-1]['type'] == 'procedure':
            content = p[-1]['content']
            return_expr = []
            if func['return'] == '__return__':
                for expr in content:
                    if expr[0] == func['return']:
                        return_expr = expr
                        break
                if return_expr[1] in func['variables'].keys():
                    # delete the last procedure, return expr[1] directly
                    func['return'] = return_expr[1]
                    func['paths'][0]['path'].pop()
                else:
                    for expr in content:
                        if expr[0] == return_expr[0]:
                            continue
                        if expr[1] == return_expr[1]:
                            return_expr = expr
                            break
                    # delete none return procedure
                    func['return'] = return_expr[0]
                    func['paths'][0]['path'][-1]['content'] = [return_expr]
                if func['return'] != '__return__':
                    func['variables'].pop('__return__')


if __name__ == "__main__":
    file_name = sys.argv[1]
    func_json = read_json(file_name)
    program_name = get_program_name(func_json)
    new_func = handle_function_json(func_json)
    simplify_return_procedure(new_func)
    new_func['program_name'] = program_name
    output_file = open(file_name + postfix_output, 'w')
    json.dump(new_func, output_file, indent=4)
    output_file.close()
    # adapt to walker's experiment
    output_file = open(file_name + postfix_output, 'r')
    content = output_file.read()
    # change 'constraint' to 'constrain'
    content = content.replace('\"constraint\":', '\"constrain\":')
    # change 'initializer' to 'initialize'
    content = content.replace('\"initializer\":', '\"initialize\":')
    # some loop optimizations are based on string comparing. there are some bugs.
    # fix these bugs with some simple string modification
    content = content.replace('\"-1+i\"', '\"i-1\"')
    content = content.replace('\"1+i\"', '\"i+1\"')
    output_file.close()
    output_file = open(program_name + postfix_output, 'w')
    output_file.write(content)
