#!/usr/bin/perl
use warnings;
use File::Copy qw(copy move);


use File::Compare;
use File::stat;
use Time::localtime;

# if (compare("file1", "file2") == 0) {
#   print "They're equal\n";
# }

my $username = getpwuid( $< );
my $rfDir = "/home/$username/roundfile";

unless(-d "$rfDir"){
    print "roundfile directory does not exist, trying to create directory ... ";
    # print "$rfDir";
    # if(system("mkdir $rfDir")){
    unless(mkdir("$rfDir")){
        die "\nUnable to create roundfile directory\n";
    } else {
        print "success!\n";
    }
}
my @files;
my @flags;
my $interactiveFlag = 0;
my $recoverFlag = 0;

sub roundfile {
    if (-f $_) {
        # print "$_ is a file\n";
        unless (-e "$rfDir/$_") {
            move($_,"$rfDir/$_") or print "rf of $_ failed\n";
        } else {
            if(compare($_,"$rfDir/$_") == 0){
                move($_,"$rfDir/$_") or print "rf of $_ failed\n";
            } else {
                my $counter = 1;
                while(-e "$rfDir/$_.$counter"){
                    $counter++;
                }
                move($_,"$rfDir/$_.$counter") or print "rf of $_ failed\n";
            }
        }
    } elsif(-d $_) {
        # print "$_ is a directory\n";
        unless(-e "$rfDir/$_") {
            if(system("mv $_ $rfDir")){
                print "rf of $_ failed\n";
            }
        } else{
            print "Directory $_ already exists in roundfile folder. Should the retreived directory replace the existing one?\n yes/no: ";
            my $response = <STDIN>;
            unless(index($response, 'yes')){
                if(system("mv $_ $rfDir")){
                    print "rf of $_ failed\n";
                } else {
                    print "Directory $rfDir/$_ overwritten.\n";
                }
            }
        }
    } else  {
        print "$_ doesn't exist as a file or directory\n";
    }
}

sub roundfileConfirm {
    # my $timestamp = ctime(stat($_)->mtime);
    if(-f $_ || -d $_){
        print "Are you sure you would like to rf $_?\n yes/no: ";
        my $response = <STDIN>;
        unless(index($response, 'yes')){
            roundfile($_);
        } else {
            print " Skipping rf-ing $_\n";
        }
    } else {
        print "$_ doesn't seem to exist as a file or directory.\n";
    }
}

sub recoverFile {
    if (-f "$rfDir/$_") {
        # print "$_ is a file\n";
        unless (-e "$_") {
            move("$rfDir/$_","$_") or print "Recovery of $_ failed\n";
        } else {
            print "File $_ already exists in current folder. Should the recovered file replace the existing one?\n yes/no: ";
            my $response = <STDIN>;
            unless(index($response, 'yes')){
                if(move("$rfDir/$_","$_")){
                    print " $_ recovered.\n";
                } else {
                    print " Recovery of $_ failed\n";
                }    
            } else {
                print " Skipped recovering $_\n";
            }
        }
    } elsif(-d "$rfDir/$_") {
        # print "$_ is a directory\n";
        unless(-e "$_") {
            if(system("mv $rfDir/$_ $_")){
                print "rf of $_ failed\n";
            }
        } else{
            print "Directory $_ already exists in roundfile folder. Should the recovered directory replace the existing one?\n yes/no: ";
            my $response = <STDIN>;
            unless(index($response, 'yes')){
                if(system("mv $rfDir/$_ $_")){
                    print "rf of $_ failed\n";
                } else {
                    print " $_ recovered.\n";
                }
            } else {
                print " Skipped recovering $_\n";
            }
        }
    } else  {
        print "$_ doesn't exist as a file or directory in the roundfile folder.\n";
    }
}

if(!@ARGV){
    die "No arguments supplied\n";
}

# Split files from flags
foreach(@ARGV){
    if($_ =~ /-[efilrt]+/){
        push @flags, $_;
    } else {
        push @files, $_;
    }
    # print "Files: @Files\n";
}


foreach(@flags){
    if(index($_, "e") != -1){ # empty roundfile folder
        # print "in -e\n";
        my @roundfiles = <$rfDir/*>;
        foreach(@roundfiles){
            if(-f $_){
                unlink $_;
            } elsif(-d $_) {
                if(system("rm -r $_")){
                    print "rf of $_ failed\n";
                }
            }
        }
    }
    if(index($_, "f") != -1){ # delete roundfile folder
        # print "in -f\n";
        rmdir "$rfDir";
    }
    if(index($_, "i") != -1){ # confirm deletions of each file
        # print "in -i\n";
        $interactiveFlag = 1;
    }
    if(index($_, "r") != -1){ # recover files
        # print "in -r\n";
        $recoverFlag = 1;
    }
    if(index($_, "l") != -1){ # list current files in roundfile
        # print "in -l\n";
        my @roundfiles = <$rfDir/*>;
        if(@roundfiles){
            print "Listing files in $rfDir:\n";
            foreach(@roundfiles){
                print "  $_\n";
            }
        } else {
            print "$rfDir is empty\n";
        }
    }
    # For easily creating test files
    if(index($_, "t") != -1){ # recover files
        # print "in -r\n";
        system("touch 1.txt 2.txt 3.txt");
    }
}

# This seems like an 'unreasonable' combination to me
if($interactiveFlag == 1 && $recoverFlag == 1){
    die "error: Cannot use both -i and -r flags together\n";
}

if($interactiveFlag == 1){
    foreach(@files){
        roundfileConfirm($_);
    }
} elsif($recoverFlag == 1){
    foreach(@files){
        recoverFile($_);
    }
} else {
    foreach(@files){
        roundfile($_);
    }
}