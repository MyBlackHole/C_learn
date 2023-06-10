# 相关
# msgmerge msginit ngettext localeconv
xgettext -k --from-code=utf-8 --keyword=gettext dome.c -o dome.pot
cp dome.pot zh_CN.po
msgfmt zh_CN.po -o dome.mo
cp dome.mo ./zh_CN/LC_MESSAGES
export LC_ALL=zh_CN.UTF-8
