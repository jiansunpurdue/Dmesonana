#!/usr/local/bin/perl

sub produce_small_file_segment;

$type = $ARGV[0];
$filelist = $ARGV[1];
$njobs = $ARGV[2];
#$HOME = "/home/sun229";


$HOME = "/home/sun229/DmesonAna";
#$BASE = "/usr/rmt_share/scratch96/w/wxie";
$BASE = "/home/sun229/DmesonAna";
$workarea = "$BASE/sl6ana/v1_pbpb_pp_pPb/CMSSW_5_3_20/src/UserCode/OpenHF/Dmesonana";

open(FILE, "$filelist");
@lines = <FILE>;
close(FILE);

$itotal = @lines;

print "number of files: $itotal \n";


$ntot = 0;
$nfiles = int($itotal/$njobs)+1;
for ($ifile = 0; $ifile < $njobs ; $ifile ++) {

    $istart = $ifile*$nfiles;
    $iend = $nfiles + $istart;

    if($iend >$itotal) {
        $iend = $itotal;
    }

    if($istart < $start_from) {
        next;
    }

    #-- produce job exec file ...
    $job_execfile = "rundana\_$istart\_$iend\_$type";

    #-- produce condor configuration file ...
    $config_file = "rundana\_$istart\_$iend\_$type.job";
    &produce_config_file;

    system("condor_submit $config_file");

    if($iend == $itotal) {
        last;
    }
}


#-----------------------------------------------------
# produce condor configuation file for each file list  

sub produce_config_file {
    open(OUTPUTFILE,">$config_file");

    print OUTPUTFILE ("#======================================================================\n");
    print OUTPUTFILE ("#\n");
    print OUTPUTFILE ("# condor_submit condor_job\n");
    print OUTPUTFILE ("#\n");
    print OUTPUTFILE ("#======================================================================\n");
    print OUTPUTFILE ("universe             = vanilla\n");
    print OUTPUTFILE ("executable           = run_Dmesonana.sh\n");
	print OUTPUTFILE ("Arguments = $istart $iend $filelist $type\n");
    print OUTPUTFILE ("initialdir           = $workarea\n");
    print OUTPUTFILE ("should_Transfer_Files = NO\n");
#	print OUTPUTFILE ("requirements = (Arch == \"X86_64\")&&regexp(\"cms\",Name)\n");
	print OUTPUTFILE ("Requirements   = Arch == \"X86_64\" && TARGET.UidDomain == \"rcac.purdue.edu\" && TARGET.Machine != \"airplay-render1.rcac.purdue.edu\" && TARGET.Machine != \"airplay-render2.rcac.purdue.edu\"\n");
    print OUTPUTFILE ("#======================================================================\n");
    print OUTPUTFILE ("output               = $job_execfile.out\n");
    print OUTPUTFILE ("error                = $job_execfile.err\n");
    print OUTPUTFILE ("log                  = $job_execfile.log\n");
	print OUTPUTFILE ("#======================================================================\n");
	print OUTPUTFILE ("Getenv               = True\n");
    print OUTPUTFILE ("#======================================================================\n");
    print OUTPUTFILE ("\n");
#    print OUTPUTFILE ("requirements = (Arch == \"X86_64\")||regexp(\"cms\",Name) \n");
#	print OUTPUTFILE ("globus_rsl = (condor_submit=(requirements 'regexp(\"cms-*\",Machine)'))\n");
    print OUTPUTFILE ("#======================================================================\n");
    print OUTPUTFILE ("+CMSJob = True\n");
    print OUTPUTFILE ("#+LENGTH=\"SHORT\"\n");
    print OUTPUTFILE ("\n");
    print OUTPUTFILE ("queue\n");
    print OUTPUTFILE ("\n");
}
