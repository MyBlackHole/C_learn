# 相关
# msgmerge msginit ngettext localeconv
xgettext -k --from-code=utf-8 --keyword=gettext demo.c -o demo.pot
cp demo.pot zh_CN.po
msgfmt zh_CN.po -o dome.mo
cp demo.mo ./zh_CN/LC_MESSAGES
export LC_ALL=zh_CN.UTF-8
