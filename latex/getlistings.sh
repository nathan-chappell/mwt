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

common_h="../cpp/include/common.h"
common_cpp="../cpp/src/common.cpp"
hcone_h="../cpp/include/hcone.h"
hcone_cpp="../cpp/src/hcone.cpp"
vcone_h="../cpp/include/vcone.h"
vcone_cpp="../cpp/src/vcone.cpp"
poly_cpp="../cpp/src/polyhedra.cpp"

make_command "lstVecMat"     "/using Vector/,/using Matrix/" "$common_h"
make_command "lstVPoly"      "/struct VPoly/,/$close_brace/" "$common_h"
make_command "lstD"          "/extern size_t d;/"            "$common_h"
make_command "lstIstream"    "/operator>>/, /$blank_line/"   "$common_h"
make_command "lstOstream"    "/operator<</, /$blank_line/"   "$common_h"
make_command "lstInputError" "/class input_error/"           "$common_h"
make_command "lstUsage"      "/int usage();/"                "$common_h"
make_command "lstTranspose"  "/Matrix transpose(/"           "$common_h"
make_command "lstProjectM"   "/Matrix project_matrix(/"      "$common_h"

make_command "lstCheckEmpty"   "/bool check_empty_matrix(/,/$close_brace/" "$common_cpp"
make_command "lstFME"          "/Matrix fourier_motzkin(/,/$close_brace/"  "$common_cpp"
make_command "lstFMEPart"      "/const auto z_end/,/return v\[k\] > 0;/"   "$common_cpp"
make_command "lstFMEMove"      "/move(M.begin()/"                          "$common_cpp"
make_command "lstFMEConvolute" "/for (auto p_it = z_end/,/^  }/"           "$common_cpp"

make_command "lstLiftHcone"      "/Matrix lift_hcone(/"                    "$hcone_h"
make_command "lstIntersectVCone" "/Matrix intersect_vcone/,/$close_brace/" "$hcone_cpp"
make_command "lstHconeToVcone"   "/Matrix hcone_to_vcone/,/$close_brace/"  "$hcone_cpp"

make_command "lstLiftVcone"      "/Matrix lift_vcone(/"                    "$vcone_h"
make_command "lstProjectHCone"   "/Matrix project_hcone/,/$close_brace/"   "$vcone_cpp"
make_command "lstVconeToHcone"   "/Matrix vcone_to_hcone/,/$close_brace/"  "$vcone_cpp"

make_command "lstProjectZero"    "/Matrix project_zero(/,/$close_brace/"   "$poly_cpp"
make_command "lstNormalizeP"     "/Matrix normalize_P(/,/$close_brace/"    "$poly_cpp"
make_command "lstHpolyToHCone"   "/Matrix hpoly_to_hcone(/,/$close_brace/" "$poly_cpp"
make_command "lstHconeToHPoly"   "/Matrix hcone_to_hpoly(/,/$close_brace/" "$poly_cpp"
make_command "lstVpolyToVCone"   "/Matrix vpoly_to_vcone(/,/$close_brace/" "$poly_cpp"
make_command "lstVconeToVPoly"   "/VPoly vcone_to_vpoly(/,/$close_brace/"  "$poly_cpp"
make_command "lstHpolyToVPoly"   "/VPoly hpoly_to_vpoly(/,/$close_brace/"  "$poly_cpp"
make_command "lstVpolyToHPoly"   "/Matrix vpoly_to_hpoly(/,/$close_brace/" "$poly_cpp"
