#!/bin/bash

LISTING=""

# $1 range, $2 file
get_listing() {
  lines=( $(eval "sed -n '$1 =' $2") )
  LISTING="\\lstinputlisting[firstline=${lines[0]}, firstnumber=${lines[0]}, lastline=${lines[-1]}]{$2}"
}

# $1 begin, $2 end, $3 file, $4 newcommand name
make_command() {
  get_listing "$2" "$3"
  echo "\\newcommand{\\$1}{$LISTING}"
}

close_brace="^}"
blank_line="^$"

make_command "lstVecMat"     "/using Vector/,/using Matrix/" "../cpp/include/common.h"
make_command "lstVPoly"      "/struct VPoly/,/$close_brace/" "../cpp/include/common.h"
make_command "lstD"          "/extern size_t d;/"            "../cpp/include/common.h"
make_command "lstIstream"    "/operator>>/, /$blank_line/"   "../cpp/include/common.h"
make_command "lstOstream"    "/operator<</, /$blank_line/"   "../cpp/include/common.h"
make_command "lstInputError" "/class input_error/"           "../cpp/include/common.h"
make_command "lstUsage"      "/int usage();/"                "../cpp/include/common.h"
make_command "lstTranspose"  "/Matrix transpose(/"           "../cpp/include/common.h"
make_command "lstProjectM"   "/Matrix project_matrix(/"      "../cpp/include/common.h"

make_command "lstCheckEmpty" "/bool check_empty_matrix(/,/$close_brace/" \
                                                             "../cpp/src/common.cpp"
make_command "lstFourierMotzkin" "/Matrix fourier_motzkin(/,/$close_brace/" \
                                                             "../cpp/src/common.cpp"
make_command "lstFourierMotzkinPart" "/const auto z_end/,/return v\[k\] > 0;/" \
                                                             "../cpp/src/common.cpp"
make_command "lstFourierMotzkinMove" "/move(M.begin()/"      "../cpp/src/common.cpp"
make_command "lstFourierMotzkinConvolute" "/for (auto p_it = z_end/,/^  }/"\
                                                             "../cpp/src/common.cpp"

make_command "lstLiftHcone"       "/Matrix lift_hcone(/"     "../cpp/include/hcone.h"
make_command "lstIntersectVCone"  "/Matrix intersect_vcone/,/$close_brace/"\
                                                             "../cpp/src/hcone.cpp"
make_command "lstHconeToVcone"    "/Matrix hcone_to_vcone/,/$close_brace/"\
                                                             "../cpp/src/hcone.cpp"
