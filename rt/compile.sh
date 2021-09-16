#!/bin/bash

# 总结了所有指令
# https://gitee.com/openeuler/docs/edit/stable2-20.03_LTS_SP1/docs/zh/docs/Virtualization/LibcarePlus.md
# 荣涛
# 2021年9月14日

function test_by_hand() {
# 
gcc -S foo.c
gcc -S bar.c

# 
sed -i 's/bar.c/foo.c/' bar.s
kpatch_gensrc --os=rhel6 -i foo.s -i bar.s -o foobar.s --force-global

# 
gcc -o foo foo.s
gcc -o foobar foobar.s -Wl,-q

#
kpatch_strip --strip foobar foobar.stripped
kpatch_strip --rel-fixup foo foobar.stripped
strip --strip-unneeded foobar.stripped
kpatch_strip --undo-link foo foobar.stripped

# 
str=$(readelf -n foo | grep 'Build ID')
substr=${str##* }
kpatch_make -b $substr foobar.stripped -o foo.kpatch
}

function test_by_script() {
diff -up foo.c bar.c > foo.patch
libcare-patch-make --clean foo.patch
}

test_by_hand

# 编译生成热补丁
test_by_script $*

# 执行程序
./lpmake/foo

# 打开一个新的窗口

# 在另一个窗口上执行
# libcare-ctl -v patch -p $(pidof foo) ./foo.kpatch

# 卸载热补丁
# libcare-ctl unpatch -p $(pidof foo)







