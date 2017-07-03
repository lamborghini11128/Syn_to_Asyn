/////////////////////////////////////////////////////////////
// Created by: Synopsys DC Expert(TM) in wire load mode
// Version   : K-2015.06-SP3
// Date      : Fri Jun 30 16:03:52 2017
/////////////////////////////////////////////////////////////


module test1 ( a, b, c, clk, rst );
  input [7:0] a;
  input [7:0] b;
  output [7:0] c;
  input clk, rst;
  wire   N4, N5, N6, N7, N8, N9, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12,
         n13, n14, n15, n16, n17, n18, n19, n20, n21, n22, n23, n24, n25, n26,
         n27, n28, n29, n30, n31, n32, n33, n34, n35, n36, n37, n38, n39, n40,
         n41, n42, n43, n44, n45, n46, n47, n48, n49, n50, n51, n52, n53, n54,
         n55, n56, n57, n58, n59, n60, n61, n62, n63, n64, n65, n66, n67, n68,
         n69, n70, n71, n72, n73, n74, n75, n76, n77, n78, n79, n80, n81, n82,
         n83, n84, n85, n86, n87, n88, n89, n90, n91, n92, n93, n94, n95, n96,
         n97, n98, n99, n100, n101, n102, n103, n104, n105, n106, n107, n108,
         n109, n110, n111, n112, n113, n114, n115, n116, n117, n118, n119,
         n120, n121, n122, n123, n124, n125, n126, n127, n128, n129, n130,
         n131, n132, n133, n134, n135, n136, n137, n138, n139, n140, n141,
         n142, n143, n144, n145, n146, n147, n148, n149, n150, n151, n152,
         n153, n154, n155, n156, n157, n158, n159, n160, n161, n162, n163,
         n164, n165, n166, n167, n168, n169, n170, n171, n172, n173, n174;
  wire   [7:0] next_counter;
  wire   [7:0] counter;
  wire   [7:0] next_p1;
  wire   [7:0] p1;
  wire   [7:0] next_p2;
  wire   [7:0] p2;
  wire   [7:1] \add_20/carry ;
  wire   [7:2] \add_16/carry ;

  DFFQX1 \p2_reg[7]  ( .D(next_p2[7]), .CK(clk), .Q(p2[7]) );
  DFFQX1 \counter_reg[7]  ( .D(next_counter[7]), .CK(clk), .Q(counter[7]) );
  DFFQX1 \p2_reg[6]  ( .D(next_p2[6]), .CK(clk), .Q(p2[6]) );
  DFFQX1 \p2_reg[4]  ( .D(next_p2[4]), .CK(clk), .Q(p2[4]) );
  DFFQX1 \p1_reg[3]  ( .D(next_p1[3]), .CK(clk), .Q(p1[3]) );
  DFFQX1 \p1_reg[0]  ( .D(next_p1[0]), .CK(clk), .Q(p1[0]) );
  DFFQX1 \p2_reg[5]  ( .D(next_p2[5]), .CK(clk), .Q(p2[5]) );
  DFFQX1 \p1_reg[4]  ( .D(next_p1[4]), .CK(clk), .Q(p1[4]) );
  DFFQX1 \p2_reg[0]  ( .D(next_p2[0]), .CK(clk), .Q(p2[0]) );
  DFFQX1 \p1_reg[5]  ( .D(next_p1[5]), .CK(clk), .Q(p1[5]) );
  DFFQX1 \p1_reg[6]  ( .D(next_p1[6]), .CK(clk), .Q(p1[6]) );
  DFFQX1 \p1_reg[7]  ( .D(next_p1[7]), .CK(clk), .Q(p1[7]) );
  DFFQX1 \p1_reg[1]  ( .D(next_p1[1]), .CK(clk), .Q(p1[1]) );
  DFFQX1 \p2_reg[3]  ( .D(next_p2[3]), .CK(clk), .Q(p2[3]) );
  DFFQX1 \p1_reg[2]  ( .D(next_p1[2]), .CK(clk), .Q(p1[2]) );
  DFFQX1 \p2_reg[2]  ( .D(next_p2[2]), .CK(clk), .Q(p2[2]) );
  DFFQX1 \p2_reg[1]  ( .D(next_p2[1]), .CK(clk), .Q(p2[1]) );
  DFFQX1 \counter_reg[6]  ( .D(next_counter[6]), .CK(clk), .Q(counter[6]) );
  DFFQX1 \counter_reg[5]  ( .D(next_counter[5]), .CK(clk), .Q(counter[5]) );
  DFFQX1 \counter_reg[4]  ( .D(next_counter[4]), .CK(clk), .Q(counter[4]) );
  DFFQX1 \counter_reg[0]  ( .D(next_counter[0]), .CK(clk), .Q(counter[0]) );
  DFFQX1 \counter_reg[1]  ( .D(next_counter[1]), .CK(clk), .Q(counter[1]) );
  DFFQX1 \counter_reg[3]  ( .D(next_counter[3]), .CK(clk), .Q(counter[3]) );
  DFFQX1 \counter_reg[2]  ( .D(next_counter[2]), .CK(clk), .Q(counter[2]) );
  XOR3X1 \add_20/U1_7  ( .A(a[7]), .B(b[7]), .C(\add_20/carry [7]), .Y(
        next_p1[7]) );
  ADDHXL \add_16/U1_1_6  ( .A(counter[6]), .B(\add_16/carry [6]), .CO(
        \add_16/carry [7]), .S(N9) );
  ADDFXL \add_20/U1_0  ( .A(a[0]), .B(b[0]), .CI(1'b0), .CO(\add_20/carry [1]), 
        .S(next_p1[0]) );
  ADDFXL \add_20/U1_6  ( .A(a[6]), .B(b[6]), .CI(\add_20/carry [6]), .CO(
        \add_20/carry [7]), .S(next_p1[6]) );
  ADDFXL \add_20/U1_5  ( .A(a[5]), .B(b[5]), .CI(\add_20/carry [5]), .CO(
        \add_20/carry [6]), .S(next_p1[5]) );
  ADDFXL \add_20/U1_4  ( .A(a[4]), .B(b[4]), .CI(\add_20/carry [4]), .CO(
        \add_20/carry [5]), .S(next_p1[4]) );
  ADDFXL \add_20/U1_3  ( .A(a[3]), .B(b[3]), .CI(\add_20/carry [3]), .CO(
        \add_20/carry [4]), .S(next_p1[3]) );
  ADDFXL \add_20/U1_2  ( .A(a[2]), .B(b[2]), .CI(\add_20/carry [2]), .CO(
        \add_20/carry [3]), .S(next_p1[2]) );
  ADDFXL \add_20/U1_1  ( .A(a[1]), .B(b[1]), .CI(\add_20/carry [1]), .CO(
        \add_20/carry [2]), .S(next_p1[1]) );
  ADDHXL \add_16/U1_1_5  ( .A(counter[5]), .B(\add_16/carry [5]), .CO(
        \add_16/carry [6]), .S(N8) );
  ADDHXL \add_16/U1_1_4  ( .A(counter[4]), .B(\add_16/carry [4]), .CO(
        \add_16/carry [5]), .S(N7) );
  ADDHXL \add_16/U1_1_3  ( .A(counter[3]), .B(\add_16/carry [3]), .CO(
        \add_16/carry [4]), .S(N6) );
  ADDHXL \add_16/U1_1_2  ( .A(counter[2]), .B(\add_16/carry [2]), .CO(
        \add_16/carry [3]), .S(N5) );
  ADDHXL \add_16/U1_1_1  ( .A(counter[1]), .B(counter[0]), .CO(
        \add_16/carry [2]), .S(N4) );
  OAI21XL U12 ( .A0(n3), .A1(n4), .B0(n5), .Y(next_p2[7]) );
  XOR2X1 U13 ( .A(n6), .B(n3), .Y(next_p2[6]) );
  AOI21X1 U14 ( .A0(n7), .A1(n8), .B0(n9), .Y(n3) );
  OA21XL U15 ( .A0(n8), .A1(n7), .B0(n10), .Y(n9) );
  NAND2BX1 U16 ( .AN(n4), .B(n5), .Y(n6) );
  OA21XL U17 ( .A0(n11), .A1(n12), .B0(n13), .Y(n5) );
  OAI2BB1X1 U18 ( .A0N(n11), .A1N(n12), .B0(n14), .Y(n13) );
  NAND2X1 U19 ( .A(p1[7]), .B(p1[3]), .Y(n4) );
  XOR2X1 U20 ( .A(n8), .B(n15), .Y(next_p2[5]) );
  XOR2X1 U21 ( .A(n10), .B(n7), .Y(n15) );
  OAI21XL U22 ( .A0(n16), .A1(n17), .B0(n18), .Y(n7) );
  AO21X1 U23 ( .A0(n17), .A1(n16), .B0(n19), .Y(n18) );
  OAI22XL U24 ( .A0(n20), .A1(n21), .B0(n22), .B1(n23), .Y(n10) );
  AND2X1 U25 ( .A(n21), .B(n20), .Y(n22) );
  XOR2X1 U26 ( .A(n24), .B(n11), .Y(n8) );
  NAND2X1 U27 ( .A(p1[2]), .B(p1[7]), .Y(n11) );
  XOR2X1 U28 ( .A(n14), .B(n12), .Y(n24) );
  NAND2X1 U29 ( .A(p1[6]), .B(p1[3]), .Y(n12) );
  AND3X1 U30 ( .A(p1[1]), .B(n25), .C(p1[7]), .Y(n14) );
  XNOR2X1 U31 ( .A(n17), .B(n26), .Y(next_p2[4]) );
  XOR2X1 U32 ( .A(n19), .B(n16), .Y(n26) );
  AOI2BB2X1 U33 ( .B0(n27), .B1(n28), .A0N(n29), .A1N(n30), .Y(n16) );
  NOR2X1 U34 ( .A(n28), .B(n27), .Y(n30) );
  AOI2BB1X1 U35 ( .A0N(n31), .A1N(n32), .B0(n33), .Y(n19) );
  XNOR2X1 U36 ( .A(n34), .B(n20), .Y(n17) );
  XNOR2X1 U37 ( .A(n25), .B(n35), .Y(n20) );
  AND2X1 U38 ( .A(p1[1]), .B(p1[7]), .Y(n35) );
  AND2X1 U39 ( .A(p1[5]), .B(p1[3]), .Y(n25) );
  XNOR2X1 U40 ( .A(n23), .B(n21), .Y(n34) );
  NAND2X1 U41 ( .A(p1[6]), .B(p1[2]), .Y(n21) );
  NAND3X1 U42 ( .A(p1[2]), .B(p1[5]), .C(n36), .Y(n23) );
  XNOR2X1 U43 ( .A(n27), .B(n37), .Y(next_p2[3]) );
  XOR2X1 U44 ( .A(n29), .B(n28), .Y(n37) );
  XNOR2X1 U45 ( .A(n31), .B(n38), .Y(n28) );
  NOR2X1 U46 ( .A(n33), .B(n32), .Y(n38) );
  NAND2X1 U47 ( .A(p1[6]), .B(p1[1]), .Y(n32) );
  NOR3X1 U48 ( .A(n39), .B(n40), .C(n41), .Y(n33) );
  NAND2X1 U49 ( .A(p1[0]), .B(p1[7]), .Y(n31) );
  OA21XL U50 ( .A0(n42), .A1(n43), .B0(n44), .Y(n29) );
  OAI2BB1X1 U51 ( .A0N(n43), .A1N(n42), .B0(n45), .Y(n44) );
  XOR2X1 U52 ( .A(n36), .B(n46), .Y(n27) );
  AND2X1 U53 ( .A(p1[5]), .B(p1[2]), .Y(n46) );
  AND2X1 U54 ( .A(p1[3]), .B(p1[4]), .Y(n36) );
  XNOR2X1 U55 ( .A(n42), .B(n47), .Y(next_p2[2]) );
  XNOR2X1 U56 ( .A(n45), .B(n43), .Y(n47) );
  NAND2X1 U57 ( .A(p1[4]), .B(p1[2]), .Y(n43) );
  NOR3BXL U58 ( .AN(p1[1]), .B(n48), .C(n49), .Y(n45) );
  XOR2X1 U59 ( .A(n39), .B(n50), .Y(n42) );
  NOR2X1 U60 ( .A(n40), .B(n41), .Y(n50) );
  CLKINVX1 U61 ( .A(p1[6]), .Y(n40) );
  NAND2X1 U62 ( .A(p1[1]), .B(p1[5]), .Y(n39) );
  XOR2X1 U63 ( .A(n49), .B(n51), .Y(next_p2[1]) );
  NAND2X1 U64 ( .A(p1[4]), .B(p1[1]), .Y(n51) );
  NAND2X1 U65 ( .A(p1[0]), .B(p1[5]), .Y(n49) );
  NOR2X1 U66 ( .A(n48), .B(n41), .Y(next_p2[0]) );
  CLKINVX1 U67 ( .A(p1[0]), .Y(n41) );
  CLKINVX1 U68 ( .A(p1[4]), .Y(n48) );
  NOR2X1 U69 ( .A(rst), .B(n52), .Y(next_counter[7]) );
  XNOR2X1 U70 ( .A(counter[7]), .B(\add_16/carry [7]), .Y(n52) );
  NOR2BX1 U71 ( .AN(N9), .B(rst), .Y(next_counter[6]) );
  NOR2BX1 U72 ( .AN(N8), .B(rst), .Y(next_counter[5]) );
  NOR2BX1 U73 ( .AN(N7), .B(rst), .Y(next_counter[4]) );
  NOR2BX1 U74 ( .AN(N6), .B(rst), .Y(next_counter[3]) );
  NOR2BX1 U75 ( .AN(N5), .B(rst), .Y(next_counter[2]) );
  NOR2BX1 U76 ( .AN(N4), .B(rst), .Y(next_counter[1]) );
  NOR2X1 U77 ( .A(rst), .B(counter[0]), .Y(next_counter[0]) );
  XOR2X1 U78 ( .A(n53), .B(n54), .Y(c[7]) );
  XOR2X1 U79 ( .A(n55), .B(n56), .Y(n54) );
  XOR2X1 U80 ( .A(n57), .B(n58), .Y(n56) );
  NAND2X1 U81 ( .A(counter[4]), .B(p2[3]), .Y(n58) );
  OAI22XL U82 ( .A0(n59), .A1(n60), .B0(n61), .B1(n62), .Y(n57) );
  AND2X1 U83 ( .A(n60), .B(n59), .Y(n62) );
  XOR2X1 U84 ( .A(n63), .B(n64), .Y(n55) );
  XOR2X1 U85 ( .A(n65), .B(n66), .Y(n64) );
  XOR2X1 U86 ( .A(n67), .B(n68), .Y(n66) );
  NAND2X1 U87 ( .A(p2[2]), .B(counter[5]), .Y(n68) );
  NAND2X1 U88 ( .A(p2[1]), .B(counter[6]), .Y(n67) );
  XOR2X1 U89 ( .A(n69), .B(n70), .Y(n65) );
  NAND2X1 U90 ( .A(p2[6]), .B(counter[1]), .Y(n70) );
  NAND2X1 U91 ( .A(counter[3]), .B(p2[4]), .Y(n69) );
  XOR2X1 U92 ( .A(n71), .B(n72), .Y(n63) );
  XOR2X1 U93 ( .A(n73), .B(n74), .Y(n72) );
  NAND2X1 U94 ( .A(p2[7]), .B(counter[0]), .Y(n74) );
  NAND2X1 U95 ( .A(p2[5]), .B(counter[2]), .Y(n73) );
  XOR2X1 U96 ( .A(n75), .B(n76), .Y(n71) );
  NOR2X1 U97 ( .A(n77), .B(n78), .Y(n76) );
  NOR2BX1 U98 ( .AN(counter[7]), .B(n79), .Y(n75) );
  XOR2X1 U99 ( .A(n80), .B(n81), .Y(n53) );
  XOR2X1 U100 ( .A(n82), .B(n83), .Y(n81) );
  OAI2BB1X1 U101 ( .A0N(n84), .A1N(n85), .B0(n86), .Y(n83) );
  OAI21XL U102 ( .A0(n85), .A1(n84), .B0(n87), .Y(n86) );
  OAI21XL U103 ( .A0(n88), .A1(n89), .B0(n90), .Y(n82) );
  OAI2BB1X1 U104 ( .A0N(n88), .A1N(n89), .B0(n91), .Y(n90) );
  XNOR2X1 U105 ( .A(n92), .B(n93), .Y(n80) );
  OAI21XL U106 ( .A0(n94), .A1(n95), .B0(n96), .Y(n93) );
  OAI21XL U107 ( .A0(n97), .A1(n98), .B0(n99), .Y(n96) );
  OAI2BB1X1 U108 ( .A0N(n100), .A1N(n101), .B0(n102), .Y(n92) );
  OAI21XL U109 ( .A0(n101), .A1(n100), .B0(n103), .Y(n102) );
  XOR2X1 U110 ( .A(n101), .B(n104), .Y(c[6]) );
  XOR2X1 U111 ( .A(n103), .B(n100), .Y(n104) );
  OAI21XL U112 ( .A0(n105), .A1(n106), .B0(n107), .Y(n100) );
  OAI2BB1X1 U113 ( .A0N(n106), .A1N(n105), .B0(n108), .Y(n107) );
  OAI21XL U114 ( .A0(n109), .A1(n110), .B0(n111), .Y(n103) );
  OAI21XL U115 ( .A0(n112), .A1(n113), .B0(n114), .Y(n111) );
  XNOR2X1 U116 ( .A(n115), .B(n95), .Y(n101) );
  CLKINVX1 U117 ( .A(n97), .Y(n95) );
  XOR2X1 U118 ( .A(n116), .B(n61), .Y(n97) );
  OA22X1 U119 ( .A0(n117), .A1(n118), .B0(n119), .B1(n120), .Y(n61) );
  AND2X1 U120 ( .A(n118), .B(n117), .Y(n119) );
  XNOR2X1 U121 ( .A(n60), .B(n59), .Y(n116) );
  NAND2X1 U122 ( .A(counter[4]), .B(p2[2]), .Y(n59) );
  NAND2X1 U123 ( .A(counter[3]), .B(p2[3]), .Y(n60) );
  XOR2X1 U124 ( .A(n98), .B(n99), .Y(n115) );
  OAI21XL U125 ( .A0(n121), .A1(n122), .B0(n123), .Y(n99) );
  OAI2BB1X1 U126 ( .A0N(n121), .A1N(n122), .B0(n124), .Y(n123) );
  CLKINVX1 U127 ( .A(n94), .Y(n98) );
  XOR2X1 U128 ( .A(n125), .B(n84), .Y(n94) );
  XNOR2X1 U129 ( .A(n88), .B(n126), .Y(n84) );
  XNOR2X1 U130 ( .A(n91), .B(n89), .Y(n126) );
  NAND2X1 U131 ( .A(p2[4]), .B(counter[2]), .Y(n89) );
  AND2X1 U132 ( .A(counter[6]), .B(p2[0]), .Y(n91) );
  NAND2X1 U133 ( .A(p2[1]), .B(counter[5]), .Y(n88) );
  XNOR2X1 U134 ( .A(n87), .B(n85), .Y(n125) );
  XOR2X1 U135 ( .A(n78), .B(n77), .Y(n85) );
  NAND2X1 U136 ( .A(p2[6]), .B(counter[0]), .Y(n77) );
  NAND2X1 U137 ( .A(counter[1]), .B(p2[5]), .Y(n78) );
  NOR3X1 U138 ( .A(n127), .B(n128), .C(n129), .Y(n87) );
  XOR2X1 U139 ( .A(n130), .B(n106), .Y(c[5]) );
  XNOR2X1 U140 ( .A(n131), .B(n113), .Y(n106) );
  CLKINVX1 U141 ( .A(n109), .Y(n113) );
  XNOR2X1 U142 ( .A(n132), .B(n117), .Y(n109) );
  XOR2X1 U143 ( .A(n127), .B(n133), .Y(n117) );
  NOR2X1 U144 ( .A(n128), .B(n129), .Y(n133) );
  NAND2X1 U145 ( .A(p2[5]), .B(counter[0]), .Y(n127) );
  XNOR2X1 U146 ( .A(n118), .B(n120), .Y(n132) );
  NAND2X1 U147 ( .A(p2[2]), .B(counter[3]), .Y(n120) );
  NAND2X1 U148 ( .A(counter[4]), .B(p2[1]), .Y(n118) );
  XOR2X1 U149 ( .A(n112), .B(n114), .Y(n131) );
  OAI21XL U150 ( .A0(n134), .A1(n135), .B0(n136), .Y(n114) );
  OAI2BB1X1 U151 ( .A0N(n134), .A1N(n135), .B0(n137), .Y(n136) );
  CLKINVX1 U152 ( .A(n110), .Y(n112) );
  XNOR2X1 U153 ( .A(n138), .B(n121), .Y(n110) );
  NAND2X1 U154 ( .A(counter[5]), .B(p2[0]), .Y(n121) );
  XOR2X1 U155 ( .A(n124), .B(n122), .Y(n138) );
  NAND2X1 U156 ( .A(p2[3]), .B(counter[2]), .Y(n122) );
  AND3X1 U157 ( .A(n139), .B(counter[1]), .C(p2[3]), .Y(n124) );
  XOR2X1 U158 ( .A(n108), .B(n105), .Y(n130) );
  OA21XL U159 ( .A0(n140), .A1(n141), .B0(n142), .Y(n105) );
  AO21X1 U160 ( .A0(n141), .A1(n140), .B0(n143), .Y(n142) );
  OAI2BB1X1 U161 ( .A0N(n144), .A1N(n145), .B0(n146), .Y(n108) );
  OAI21XL U162 ( .A0(n145), .A1(n144), .B0(n147), .Y(n146) );
  XNOR2X1 U163 ( .A(n141), .B(n148), .Y(c[4]) );
  XOR2X1 U164 ( .A(n143), .B(n140), .Y(n148) );
  AOI2BB2X1 U165 ( .B0(n149), .B1(n150), .A0N(n151), .A1N(n152), .Y(n140) );
  NOR2X1 U166 ( .A(n150), .B(n149), .Y(n152) );
  AOI2BB1X1 U167 ( .A0N(n153), .A1N(n154), .B0(n155), .Y(n143) );
  XOR2X1 U168 ( .A(n156), .B(n144), .Y(n141) );
  XNOR2X1 U169 ( .A(n134), .B(n157), .Y(n144) );
  XNOR2X1 U170 ( .A(n137), .B(n135), .Y(n157) );
  NAND2X1 U171 ( .A(p2[2]), .B(counter[2]), .Y(n135) );
  AND2X1 U172 ( .A(counter[4]), .B(p2[0]), .Y(n137) );
  NAND2X1 U173 ( .A(counter[3]), .B(p2[1]), .Y(n134) );
  XNOR2X1 U174 ( .A(n147), .B(n145), .Y(n156) );
  XOR2X1 U175 ( .A(n139), .B(n158), .Y(n145) );
  NOR2X1 U176 ( .A(n129), .B(n159), .Y(n158) );
  NOR2X1 U177 ( .A(n160), .B(n128), .Y(n139) );
  CLKINVX1 U178 ( .A(p2[4]), .Y(n128) );
  AND3X1 U179 ( .A(p2[2]), .B(counter[1]), .C(n161), .Y(n147) );
  XNOR2X1 U180 ( .A(n149), .B(n162), .Y(c[3]) );
  XOR2X1 U181 ( .A(n151), .B(n150), .Y(n162) );
  XNOR2X1 U182 ( .A(n153), .B(n163), .Y(n150) );
  NOR2X1 U183 ( .A(n155), .B(n154), .Y(n163) );
  NAND2X1 U184 ( .A(counter[2]), .B(p2[1]), .Y(n154) );
  NOR3X1 U185 ( .A(n164), .B(n79), .C(n165), .Y(n155) );
  NAND2X1 U186 ( .A(counter[3]), .B(p2[0]), .Y(n153) );
  OA21XL U187 ( .A0(n166), .A1(n167), .B0(n168), .Y(n151) );
  AO21X1 U188 ( .A0(n167), .A1(n166), .B0(n169), .Y(n168) );
  XOR2X1 U189 ( .A(n161), .B(n170), .Y(n149) );
  NOR2BX1 U190 ( .AN(p2[2]), .B(n129), .Y(n170) );
  NOR2X1 U191 ( .A(n159), .B(n160), .Y(n161) );
  CLKINVX1 U192 ( .A(p2[3]), .Y(n159) );
  XNOR2X1 U193 ( .A(n166), .B(n171), .Y(c[2]) );
  XOR2X1 U194 ( .A(n169), .B(n167), .Y(n171) );
  NAND2X1 U195 ( .A(p2[2]), .B(counter[0]), .Y(n167) );
  NAND3X1 U196 ( .A(counter[0]), .B(p2[1]), .C(n172), .Y(n169) );
  XOR2X1 U197 ( .A(n165), .B(n173), .Y(n166) );
  NOR2X1 U198 ( .A(n79), .B(n164), .Y(n173) );
  CLKINVX1 U199 ( .A(counter[2]), .Y(n164) );
  NAND2X1 U200 ( .A(counter[1]), .B(p2[1]), .Y(n165) );
  XNOR2X1 U201 ( .A(n172), .B(n174), .Y(c[1]) );
  NAND2X1 U202 ( .A(counter[0]), .B(p2[1]), .Y(n174) );
  NOR2X1 U203 ( .A(n129), .B(n79), .Y(n172) );
  CLKINVX1 U204 ( .A(counter[1]), .Y(n129) );
  NOR2X1 U205 ( .A(n79), .B(n160), .Y(c[0]) );
  CLKINVX1 U206 ( .A(counter[0]), .Y(n160) );
  CLKINVX1 U207 ( .A(p2[0]), .Y(n79) );
endmodule

