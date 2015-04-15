#!/usr/bin/perl
use v5.10;
my $dir = '../../';
my $dsf = ['dsf/include/dsf', 'dsf/src/dsf', 'Dual State Framework'];
my $yctools = ['dsf/include/yctools', 'dsf/src/yctools', 'yctools'];
my $profiler = ['profiler/include', 'profiler/src', 'Benchmark Program'];
my @subdirs = ($dsf, $yctools, $profiler);

say '/**';
for $subdir(@subdirs) {
	my $page = $$subdir[2];
	$page =~ s/\s+//g;
	say "\\page $page  $$subdir[2]";
	opendir(DIR, $dir.$$subdir[0]) or die $!;
	while(my $file = readdir(DIR)) {
		unless($file =~ m/^\./){
			my $name = $file;
			my $head = '_h';
			my $source = '_cpp';
			$name =~ s/(\.hp{0,2})$//;
			say "\\section $page$name $name";
			say "\\subsection $page$name$head $file";
			say "__Path:__ <EM>\$PROJECT_DIR/$$subdir[0]/$file</EM>";
			say "\\includelineno $$subdir[0]/$file";
			my $cpp = $name.'.cpp';
			if(-s $dir.$$subdir[1].'/'.$cpp)
			{
				say "\\subsection $page$name$source $cpp";
				say "__Path:__ <EM>\$PROJECT_DIR/$$subdir[1]/$cpp</EM>";
				say "\\includelineno $$subdir[1]/$cpp";
			}
		}
	}
	closedir(DIR);
}
say '*/';
exit 0;