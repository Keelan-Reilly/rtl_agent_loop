proc apply_generics {top generic_csv} {
  if {$generic_csv eq ""} {
    return
  }
  set pairs [split $generic_csv ","]
  set generic_list {}
  foreach pair $pairs {
    if {$pair eq ""} {
      continue
    }
    lappend generic_list $pair
  }
  if {[llength $generic_list] > 0} {
    set_property generic [join $generic_list " "] [get_filesets sources_1]
  }
}

set repo_root [lindex $argv 0]
set run_dir [lindex $argv 1]
set top_name [lindex $argv 2]
set part_name [lindex $argv 3]
set xdc_path [lindex $argv 4]
set clock_period_ns [lindex $argv 5]
set jobs [lindex $argv 6]
set generic_csv [lindex $argv 7]

set project_dir [file join $run_dir project mac_array_project]
set reports_dir [file join $run_dir reports]
file mkdir $project_dir
file mkdir $reports_dir

create_project -force mac_array_project $project_dir -part $part_name

set sv_files [glob -directory [file join $repo_root hdl] *.sv]
foreach src $sv_files {
  add_files -norecurse $src
}
set mem_files [glob -nocomplain -directory [file join $repo_root data] *.mem]
foreach mem_file $mem_files {
  add_files -norecurse $mem_file
  set_property file_type {Memory File} [get_files $mem_file]
}
add_files -fileset constrs_1 $xdc_path
set_property top $top_name [current_fileset]
apply_generics $top_name $generic_csv
update_compile_order -fileset sources_1

launch_runs synth_1 -jobs $jobs
wait_on_run synth_1
open_run synth_1 -name synth_1
report_utilization -file [file join $reports_dir utilization_synth.rpt]
report_timing_summary -file [file join $reports_dir timing_synth.rpt]

launch_runs impl_1 -to_step route_design -jobs $jobs
wait_on_run impl_1
open_run impl_1 -name impl_1
report_utilization -file [file join $reports_dir utilization_impl.rpt]
report_timing_summary -file [file join $reports_dir timing_impl.rpt]
write_checkpoint -force [file join $reports_dir implemented.dcp]

close_project
