#!/bin/bash

# 总结了所有指令
# https://gitee.com/openeuler/docs/edit/stable2-20.03_LTS_SP1/docs/zh/docs/Virtualization/LibcarePlus.md
# 荣涛
# 2021年9月14日

src_src=foo.c
patch_src=bar.c

function press_any_key()
{
	echo -e "\033[1;31m>>>> $1 <<<<\033[m"
	read -r -p "Press any key to continue..." __input
}

function test_by_hand() {
# 进行汇编
gcc -S $src_src -o ${src_src%%.*}.s
gcc -S $patch_src -o ${patch_src%%.*}.s
press_any_key "Compile to assmebler done"


# 修改 bar.s 文件
sed -i "s/$patch_src/$src_src/" ${patch_src%%.*}.s
# foo.s + bar.s = foobar.s
kpatch_gensrc --os=rhel6 -i ${src_src%%.*}.s -i ${patch_src%%.*}.s \
	-o ${src_src%%.*}${patch_src%%.*}.s --force-global
press_any_key "Generate combine assmebler done"

# 利用汇编代码生成可执行文件
gcc -o ${src_src%%.*} ${src_src%%.*}.s
gcc -o ${src_src%%.*}${patch_src%%.*} ${src_src%%.*}${patch_src%%.*}.s -Wl,-q
press_any_key "Compile assmebler to ELF done"

# 利用 kpatch_strip 去除可执行程序 foo 和 foobar 的相同内容，保留制作热补丁所需要的内容。
kpatch_strip --strip ${src_src%%.*}${patch_src%%.*} ${src_src%%.*}${patch_src%%.*}.stripped
kpatch_strip --rel-fixup ${src_src%%.*} ${src_src%%.*}${patch_src%%.*}.stripped
strip --strip-unneeded ${src_src%%.*}${patch_src%%.*}.stripped
kpatch_strip --undo-link ${src_src%%.*} ${src_src%%.*}${patch_src%%.*}.stripped
press_any_key "Stripped unuseful section done"

# 制作热补丁文件 foo.kpatch
str=$(readelf -n ${src_src%%.*} | grep 'Build ID')
substr=${str##* }
kpatch_make -b $substr ${src_src%%.*}${patch_src%%.*}.stripped -o ${src_src%%.*}.kpatch
press_any_key "Generate patch file done"

}

#function test_by_script() {
#diff -up foo.c bar.c > foo.patch
#libcare-patch-make --clean foo.patch
#}

# 更新 libcare
source path.sh

test_by_hand
./${src_src%%.*}

# 编译生成热补丁
#test_by_script $*

# 执行程序
#./lpmake/foo

# 打开一个新的窗口

# 在另一个窗口上执行
# libcare-ctl -v patch -p $(pidof foo) ./foo.kpatch

# 卸载热补丁
# libcare-ctl unpatch -p $(pidof foo)







