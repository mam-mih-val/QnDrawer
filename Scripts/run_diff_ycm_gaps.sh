#!/bin/bash

executable=../build/QnDrawer
input_dir=../Input_Files/
output_dir=../Output_Files/
config_fw=../Configuration_Files/ForwardRapidity.txt
config_bw=../Configuration_Files/BackwardRapidity.txt
config_mr=../Configuration_Files/MidRapidity.txt

echo "$executable ${input_dir}PionPlus_Gt80.root ${output_dir}PionPlusBw.root $config_bw"
      $executable ${input_dir}PionPlus_Gt80.root ${output_dir}PionPlusBw.root $config_bw

echo "$executable ${input_dir}PionPlus_Gt80.root ${output_dir}PionPlusFw.root $config_fw"
      $executable ${input_dir}PionPlus_Gt80.root ${output_dir}PionPlusFw.root $config_fw

echo "$executable ${input_dir}PionPlus_Gt80.root ${output_dir}PionPlusMr.root $config_mr"
      $executable ${input_dir}PionPlus_Gt80.root ${output_dir}PionPlusMr.root $config_mr

echo "$executable ${input_dir}PionMinus_Gt80.root ${output_dir}PionMinusBw.root $config_bw"
      $executable ${input_dir}PionMinus_Gt80.root ${output_dir}PionMinusBw.root $config_bw

echo "$executable ${input_dir}PionMinus_Gt80.root ${output_dir}PionMinusFw.root $config_fw"
      $executable ${input_dir}PionMinus_Gt80.root ${output_dir}PionMinusFw.root $config_fw

echo "$executable ${input_dir}PionMinus_Gt80.root ${output_dir}PionMinusMr.root $config_mr"
      $executable ${input_dir}PionMinus_Gt80.root ${output_dir}PionMinusMr.root $config_mr

echo "$executable ${input_dir}Proton_Gt80.root ${output_dir}ProtonBw.root $config_bw"
      $executable ${input_dir}Proton_Gt80.root ${output_dir}ProtonBw.root $config_bw

echo "$executable ${input_dir}Proton_Gt80.root ${output_dir}ProtonFw.root $config_fw"
      $executable ${input_dir}Proton_Gt80.root ${output_dir}ProtonFw.root $config_fw

echo "$executable ${input_dir}Proton_Gt80.root ${output_dir}ProtonMr.root $config_mr"
      $executable ${input_dir}Proton_Gt80.root ${output_dir}ProtonMr.root $config_mr