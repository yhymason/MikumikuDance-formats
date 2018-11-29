import json
import codecs
import io
import re
src_path1 = "bone_out.txt"
dst_path1 = "bone_out_utf8.txt"
src_path2 = "motion_out.txt"
dst_path2 = "motion_out_utf8.txt"
## convert output files created by test.cpp to utf-8 encoding
with io.open(src_path1, mode="r", encoding="shift_jisx0213") as fd:
    content = fd.read()
with io.open(dst_path1, mode="w", encoding="utf-8") as fd:
    fd.write(content)
with io.open(src_path2, mode="r", encoding="shift_jisx0213", errors = "ignore") as fd:
    content = fd.read()
with io.open(dst_path2, mode="w", encoding="utf-8") as fd:
    fd.write(content)

## read data from utf8 txt files
with open(dst_path1, 'r') as file:
    bone_data = file.read()
with open(dst_path2, 'r') as file:
    motion_data = file.read()

## build bone data dictionary
bone_data_dic = {}
bone_data_list = bone_data.split('bone jp:')
for s in bone_data_list:
    ls = s.split('\n')
    if len(ls) > 1:
        bone_name = ls[0]
        x = ls[2].split(':')[1]
        y = ls[3].split(':')[1]
        z = ls[4].split(':')[1]
        pos = [x, y, z]
        bone_data_dic[bone_name] = pos
## build motion data dictionary
motion_data_dic = {}
motion_data_list = motion_data.split('frame:')
for s in motion_data_list:
    ls = s.split('\n')
    if len(ls) > 1:
        boneframe_name = ls[1].split(':')[1]
        if boneframe_name in bone_data_dic:
            frame_num = ls[0]
            x = ls[2].split(':')[1]
            y = ls[3].split(':')[1]
            z = ls[4].split(':')[1]
            qx = ls[5].split(':')[1]
            qy = ls[6].split(':')[1]
            qz = ls[7].split(':')[1]
            qw = ls[8].split(':')[1]
            vals = [[x,y,z], [qx,qy,qz,qw]]
            motion_data_dic[(boneframe_name, frame_num)] = vals

# for x in motion_data_dic:
#     print(x)
#     print(motion_data_dic[x])
print(motion_data_dic[('右肩', '505')])
print(motion_data_dic[('右腕', '505')])
# for x in bone_data_dic:
#     print(x)
#     print(bone_data_dic[x])