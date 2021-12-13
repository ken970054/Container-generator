#!/usr/bin/perl

$file_name = 'container_rect_vec_pointer.cpp';
$file_name_new = 'container_rect_vec_pointer_runNumber.cpp';
$changed_line = 14;

@run_number_case = qw/10000 20000 30000 40000 50000 60000 70000 80000 90000 100000 200000 300000 400000 500000 600000 700000 800000 900000 1000000/;


foreach $run_number (@run_number_case) {
    ## write different run number to C++ file
    open(FILE, $file_name) or die "No read file";
    open(FILE_new, '>', $file_name_new) or die "No write file";

    while(defined($line = <FILE>)) {
        print FILE_new $line;  # write new content to file
        last if($. == ($changed_line - 1)); # line number before change
    }

    my $line = <FILE>; # line 12 that I want to change
    $line =~ s/\d+/$run_number/;
    print FILE_new $line;

    # write the rest content
    while(defined($line = <FILE>)) {
        print FILE_new $line;
    }

    close(FILE);
    close(FILE_new);

		## compile and run each file, then record the elasped time
    system("g++ -std=c++11 container_rect_vec_pointer_runNumber.cpp -o container_rect_vec_pointer_runNumber");
    system("./container_rect_vec_pointer_runNumber");

    sleep(5);
    print "Finished one loop";
}
