import json
import codecs
import io

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
with open(dst_path1, 'r') as file:
    bone_data = file.read()
with open(dst_path2, 'r') as file:
    motion_data = file.read()
