
yast_modules = TEST.ycp

EXTRA_DIST = $(yast_modules)

yast_modules_ybc = $(yast_modules:.ycp=.ybc)

$(yast_modules_ybc): $(yast_modules)
	ycpc -c $<

all: $(yast_modules_ybc)

CLEANFILES = $(wildcard *.ybc)
