#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import sys
import codecs
import xml.etree.ElementTree as ET

function_id2key = {}
function_key2id = {}

field2id = {
    "RPC_INT":1,
    "RPC_STRING":2,
    "RPC_FLOAT":3,
    "RPC_BYTES":4,
    "RPC_BOOL":5,
}

all_function_list = {}

def parse_one_file(xml_file):
    tree = ET.ElementTree(file = xml_file)
    root = tree.getroot()
    for func in root:
        func_info = {}
        for child in func:
            #print(child.tag,child.attrib, child.text)
            if child.tag == "function":
                func_info["name"] = child.text
            elif child.tag == "file":
                func_info["file"] = child.text
            elif child.tag == "args":
                func_info["arg_list"] = []
                for arg in child:
                    func_info["arg_list"] += [{"type":field2id[arg.attrib["type"]], "name":arg.attrib["name"]}]
            elif child.tag == "res":
                func_info["res_list"] = []
                for arg in child:
                    func_info["res_list"] += [{"type":field2id[arg.attrib["type"]], "name":arg.attrib["name"]}]
        all_function_list[func_info["file"] + ":" + func_info["name"]] = func_info
            
def parse_all_file(path):
    files = os.listdir(path)
    for f in files:
        if os.path.splitext(f)[-1] == ".xml":
            parse_one_file(path + "/"+ f)

def sort_function():
    global function_key2id
    global function_id2key
    function_id = 1
    sorted_list = all_function_list.keys()
    sorted_list.sort()
    for function_key in sorted_list:
        function_id2key[function_id] = function_key
        function_key2id[function_key] = function_id
        function_id += 1

def write_file():
    global struct_id2name
    global struct_name2id
    global function_id2key
    with open("../gen_code/meta.cfg", 'w') as f:
        f.write('function_table_num:{num}\n'.format(num=len(all_function_list))) 
        sorted_id_list = function_id2key.keys()
        for function_id in sorted_id_list:
            function_key = function_id2key[function_id]
            function_data = all_function_list[function_key]
            f.write('function_id:{function_id},arg_num:{arg_num},res_num:{res_num},path={path},function={function}\n'.
                    format(function_id=function_id,arg_num=len(function_data["arg_list"]),res_num=len(function_data["res_list"]), 
                    path=function_data["file"],function=function_data["name"])) 
            for arg_data in function_data["arg_list"]:
                f.write('arg_type:{arg_type},arg_name:{arg_name}\n'.
                    format(arg_type=arg_data["type"], arg_name=arg_data["name"]))
            for arg_data in function_data["res_list"]:
                f.write('res_type:{res_type},arg_name:{arg_name}\n'.
                    format(res_type=arg_data["type"], arg_name=arg_data["name"]))

    with codecs.open("../gen_code/func_id.lua", "w", "utf-8") as f:
        print >>f, u'--Don\'t Edit It! Auto Generate By Tools\n'
        print >>f, u'local func_tbl = {'
        sorted_id_list = function_id2key.keys()
        for function_id in sorted_id_list:
            function_key = function_id2key[function_id]
            function_data = all_function_list[function_key]
            print >>f , u'\tFUNC_ID_{file_name}_{function_name} = {function_id},'.format(file_name=function_data["file"].upper(),
            function_name=function_data["name"].upper(), function_id=function_id)
        print >>f, u'}\n\nreturn func_tbl'
            

                
if __name__ == '__main__':
    if len(sys.argv) < 2:
        print "pls input path"
        exit(1)

    parse_all_file(sys.argv[1])
    sort_function()
    #gen_meta_cfg()
    #gen_lua_stub()
    write_file()
    print"parse rpc ok"

#    print("show function list\n",all_function_list)
#    print("show struct list\n",all_struct_list)
#    print("show struct name2id\n",struct_name2id)
#    pri
