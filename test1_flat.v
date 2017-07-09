/////////////////////////////////////////////////////////////
// Created by: Synopsys DC Expert(TM) in wire load mode
// Version   : K-2015.06-SP3
// Date      : Fri Jun 30 15:57:45 2017
/////////////////////////////////////////////////////////////


module test1 ( a, b, c, clk );
  input [7:0] a;
  input [7:0] b;
  output [7:0] c;
  input clk;
  wire   n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14, n15, n16,
         n17, n18, n19, n20, n21, n22, n23, n24, n25, n26, n27, n28, n29, n30,
         n31, n32, n33, n34, n35, n36, n37, n38, n39, n40, n41, n42, n43, n44,
         n45, n46, n47, n48, n49, n50, n51, n52, n53, n54, n55, n56, n57, n58,
         n59, n60, n61, n62, n63, n64, n65, n66, n67, n68, n69, n70, n71, n72,
         n73, n74, n75, n76, n77, n78, n79, n80, n81, n82, n83, n84, n85, n86,
         n87, n88, n89, n90, n91, n92, n93, n94, n95, n96, n97, n98, n99;
  wire   [7:0] next_p1;
  wire   [7:0] p1;
  wire   [7:0] next_p2;
  wire   [7:0] p2;
  wire   [7:1] \add_12/carry ;

  DFFQX1 \p1_reg[3]  ( .D(next_p1[3]), .CK(clk), .Q(p1[3]) );
  DFFQX1 \p2_reg[3]  ( .D(next_p2[3]), .CK(clk), .Q(p2[3]) );
  DFFQX1 \p1_reg[4]  ( .D(next_p1[4]), .CK(clk), .Q(p1[4]) );
  DFFQX1 \p1_reg[0]  ( .D(next_p1[0]), .CK(clk), .Q(p1[0]) );
  DFFQX1 \p2_reg[4]  ( .D(next_p2[4]), .CK(clk), .Q(p2[4]) );
  DFFQX1 \p2_reg[0]  ( .D(next_p2[0]), .CK(clk), .Q(p2[0]) );
  DFFQX1 \p1_reg[5]  ( .D(next_p1[5]), .CK(clk), .Q(p1[5]) );
  DFFQX1 \p2_reg[5]  ( .D(next_p2[5]), .CK(clk), .Q(p2[5]) );
  DFFQX1 \p1_reg[6]  ( .D(next_p1[6]), .CK(clk), .Q(p1[6]) );
  DFFQX1 \p2_reg[6]  ( .D(next_p2[6]), .CK(clk), .Q(p2[6]) );
  DFFQX1 \p1_reg[7]  ( .D(next_p1[7]), .CK(clk), .Q(p1[7]) );
  DFFQX1 \p2_reg[7]  ( .D(next_p2[7]), .CK(clk), .Q(p2[7]) );
  DFFQX1 \p1_reg[1]  ( .D(next_p1[1]), .CK(clk), .Q(p1[1]) );
  DFFQX1 \p2_reg[1]  ( .D(next_p2[1]), .CK(clk), .Q(p2[1]) );
  DFFQX1 \p1_reg[2]  ( .D(next_p1[2]), .CK(clk), .Q(p1[2]) );
  DFFQX1 \p2_reg[2]  ( .D(next_p2[2]), .CK(clk), .Q(p2[2]) );
  XOR3X1 \add_12/U1_7  ( .A(a[7]), .B(b[7]), .C(\add_12/carry [7]), .Y(
        next_p1[7]) );
  ADDFXL \add_12/U1_0  ( .A(a[0]), .B(b[0]), .CI(1'b0), .CO(\add_12/carry [1]), 
        .S(next_p1[0]) );
  ADDFXL \add_12/U1_6  ( .A(a[6]), .B(b[6]), .CI(\add_12/carry [6]), .CO(
        \add_12/carry [7]), .S(next_p1[6]) );
  ADDFXL \add_12/U1_5  ( .A(a[5]), .B(b[5]), .CI(\add_12/carry [5]), .CO(
        \add_12/carry [6]), .S(next_p1[5]) );
  ADDFXL \add_12/U1_4  ( .A(a[4]), .B(b[4]), .CI(\add_12/carry [4]), .CO(
        \add_12/carry [5]), .S(next_p1[4]) );
  ADDFXL \add_12/U1_3  ( .A(a[3]), .B(b[3]), .CI(\add_12/carry [3]), .CO(
        \add_12/carry [4]), .S(next_p1[3]) );
  ADDFXL \add_12/U1_2  ( .A(a[2]), .B(b[2]), .CI(\add_12/carry [2]), .CO(
        \add_12/carry [3]), .S(next_p1[2]) );
  ADDFXL \add_12/U1_1  ( .A(a[1]), .B(b[1]), .CI(\add_12/carry [1]), .CO(
        \add_12/carry [2]), .S(next_p1[1]) );
  OAI21XL U4 ( .A0(n2), .A1(n3), .B0(n4), .Y(next_p2[7]) );
  XOR2X1 U5 ( .A(n5), .B(n2), .Y(next_p2[6]) );
  AOI21X1 U6 ( .A0(n6), .A1(n7), .B0(n8), .Y(n2) );
  OA21XL U7 ( .A0(n7), .A1(n6), .B0(n9), .Y(n8) );
  NAND2BX1 U8 ( .AN(n3), .B(n4), .Y(n5) );
  OA21XL U9 ( .A0(n10), .A1(n11), .B0(n12), .Y(n4) );
  OAI2BB1X1 U10 ( .A0N(n10), .A1N(n11), .B0(n13), .Y(n12) );
  NAND2X1 U11 ( .A(p1[7]), .B(p1[3]), .Y(n3) );
  XOR2X1 U12 ( .A(n7), .B(n14), .Y(next_p2[5]) );
  XOR2X1 U13 ( .A(n9), .B(n6), .Y(n14) );
  OAI21XL U14 ( .A0(n15), .A1(n16), .B0(n17), .Y(n6) );
  AO21X1 U15 ( .A0(n16), .A1(n15), .B0(n18), .Y(n17) );
  OAI22XL U16 ( .A0(n19), .A1(n20), .B0(n21), .B1(n22), .Y(n9) );
  AND2X1 U17 ( .A(n20), .B(n19), .Y(n21) );
  XOR2X1 U18 ( .A(n23), .B(n10), .Y(n7) );
  NAND2X1 U19 ( .A(p1[2]), .B(p1[7]), .Y(n10) );
  XOR2X1 U20 ( .A(n13), .B(n11), .Y(n23) );
  NAND2X1 U21 ( .A(p1[6]), .B(p1[3]), .Y(n11) );
  AND3X1 U22 ( .A(p1[1]), .B(n24), .C(p1[7]), .Y(n13) );
  XNOR2X1 U23 ( .A(n16), .B(n25), .Y(next_p2[4]) );
  XOR2X1 U24 ( .A(n18), .B(n15), .Y(n25) );
  AOI2BB2X1 U25 ( .B0(n26), .B1(n27), .A0N(n28), .A1N(n29), .Y(n15) );
  NOR2X1 U26 ( .A(n27), .B(n26), .Y(n29) );
  AOI2BB1X1 U27 ( .A0N(n30), .A1N(n31), .B0(n32), .Y(n18) );
  XNOR2X1 U28 ( .A(n33), .B(n19), .Y(n16) );
  XNOR2X1 U29 ( .A(n24), .B(n34), .Y(n19) );
  AND2X1 U30 ( .A(p1[1]), .B(p1[7]), .Y(n34) );
  AND2X1 U31 ( .A(p1[5]), .B(p1[3]), .Y(n24) );
  XNOR2X1 U32 ( .A(n22), .B(n20), .Y(n33) );
  NAND2X1 U33 ( .A(p1[6]), .B(p1[2]), .Y(n20) );
  NAND3X1 U34 ( .A(p1[2]), .B(p1[5]), .C(n35), .Y(n22) );
  XNOR2X1 U35 ( .A(n26), .B(n36), .Y(next_p2[3]) );
  XOR2X1 U36 ( .A(n28), .B(n27), .Y(n36) );
  XNOR2X1 U37 ( .A(n30), .B(n37), .Y(n27) );
  NOR2X1 U38 ( .A(n32), .B(n31), .Y(n37) );
  NAND2X1 U39 ( .A(p1[6]), .B(p1[1]), .Y(n31) );
  NOR3X1 U40 ( .A(n38), .B(n39), .C(n40), .Y(n32) );
  NAND2X1 U41 ( .A(p1[0]), .B(p1[7]), .Y(n30) );
  OA21XL U42 ( .A0(n41), .A1(n42), .B0(n43), .Y(n28) );
  OAI2BB1X1 U43 ( .A0N(n42), .A1N(n41), .B0(n44), .Y(n43) );
  XOR2X1 U44 ( .A(n35), .B(n45), .Y(n26) );
  AND2X1 U45 ( .A(p1[5]), .B(p1[2]), .Y(n45) );
  NOR2BX1 U46 ( .AN(p1[3]), .B(n46), .Y(n35) );
  XNOR2X1 U47 ( .A(n41), .B(n47), .Y(next_p2[2]) );
  XNOR2X1 U48 ( .A(n44), .B(n42), .Y(n47) );
  NAND2X1 U49 ( .A(p1[4]), .B(p1[2]), .Y(n42) );
  NOR3BXL U50 ( .AN(p1[1]), .B(n46), .C(n48), .Y(n44) );
  XOR2X1 U51 ( .A(n38), .B(n49), .Y(n41) );
  NOR2X1 U52 ( .A(n39), .B(n40), .Y(n49) );
  CLKINVX1 U53 ( .A(p1[6]), .Y(n39) );
  NAND2X1 U54 ( .A(p1[1]), .B(p1[5]), .Y(n38) );
  XOR2X1 U55 ( .A(n48), .B(n50), .Y(next_p2[1]) );
  NAND2X1 U56 ( .A(p1[4]), .B(p1[1]), .Y(n50) );
  NAND2X1 U57 ( .A(p1[0]), .B(p1[5]), .Y(n48) );
  NOR2X1 U58 ( .A(n46), .B(n40), .Y(next_p2[0]) );
  CLKINVX1 U59 ( .A(p1[0]), .Y(n40) );
  CLKINVX1 U60 ( .A(p1[4]), .Y(n46) );
  OAI21XL U61 ( .A0(n51), .A1(n52), .B0(n53), .Y(c[7]) );
  XOR2X1 U62 ( .A(n54), .B(n51), .Y(c[6]) );
  AOI21X1 U63 ( .A0(n55), .A1(n56), .B0(n57), .Y(n51) );
  OA21XL U64 ( .A0(n56), .A1(n55), .B0(n58), .Y(n57) );
  NAND2BX1 U65 ( .AN(n52), .B(n53), .Y(n54) );
  OA21XL U66 ( .A0(n59), .A1(n60), .B0(n61), .Y(n53) );
  OAI2BB1X1 U67 ( .A0N(n59), .A1N(n60), .B0(n62), .Y(n61) );
  NAND2X1 U68 ( .A(p2[7]), .B(p2[3]), .Y(n52) );
  XOR2X1 U69 ( .A(n56), .B(n63), .Y(c[5]) );
  XOR2X1 U70 ( .A(n58), .B(n55), .Y(n63) );
  OAI21XL U71 ( .A0(n64), .A1(n65), .B0(n66), .Y(n55) );
  AO21X1 U72 ( .A0(n65), .A1(n64), .B0(n67), .Y(n66) );
  OAI22XL U73 ( .A0(n68), .A1(n69), .B0(n70), .B1(n71), .Y(n58) );
  AND2X1 U74 ( .A(n69), .B(n68), .Y(n70) );
  XOR2X1 U75 ( .A(n72), .B(n59), .Y(n56) );
  NAND2X1 U76 ( .A(p2[2]), .B(p2[7]), .Y(n59) );
  XOR2X1 U77 ( .A(n62), .B(n60), .Y(n72) );
  NAND2X1 U78 ( .A(p2[6]), .B(p2[3]), .Y(n60) );
  AND3X1 U79 ( .A(p2[1]), .B(n73), .C(p2[7]), .Y(n62) );
  XNOR2X1 U80 ( .A(n65), .B(n74), .Y(c[4]) );
  XOR2X1 U81 ( .A(n67), .B(n64), .Y(n74) );
  AOI2BB2X1 U82 ( .B0(n75), .B1(n76), .A0N(n77), .A1N(n78), .Y(n64) );
  NOR2X1 U83 ( .A(n76), .B(n75), .Y(n78) );
  AOI2BB1X1 U84 ( .A0N(n79), .A1N(n80), .B0(n81), .Y(n67) );
  XNOR2X1 U85 ( .A(n82), .B(n68), .Y(n65) );
  XNOR2X1 U86 ( .A(n73), .B(n83), .Y(n68) );
  AND2X1 U87 ( .A(p2[1]), .B(p2[7]), .Y(n83) );
  AND2X1 U88 ( .A(p2[5]), .B(p2[3]), .Y(n73) );
  XNOR2X1 U89 ( .A(n71), .B(n69), .Y(n82) );
  NAND2X1 U90 ( .A(p2[6]), .B(p2[2]), .Y(n69) );
  NAND3X1 U91 ( .A(p2[2]), .B(p2[5]), .C(n84), .Y(n71) );
  XNOR2X1 U92 ( .A(n75), .B(n85), .Y(c[3]) );
  XOR2X1 U93 ( .A(n77), .B(n76), .Y(n85) );
  XNOR2X1 U94 ( .A(n79), .B(n86), .Y(n76) );
  NOR2X1 U95 ( .A(n81), .B(n80), .Y(n86) );
  NAND2X1 U96 ( .A(p2[6]), .B(p2[1]), .Y(n80) );
  NOR3X1 U97 ( .A(n87), .B(n88), .C(n89), .Y(n81) );
  NAND2X1 U98 ( .A(p2[0]), .B(p2[7]), .Y(n79) );
  OA21XL U99 ( .A0(n90), .A1(n91), .B0(n92), .Y(n77) );
  OAI2BB1X1 U100 ( .A0N(n91), .A1N(n90), .B0(n93), .Y(n92) );
  XOR2X1 U101 ( .A(n84), .B(n94), .Y(n75) );
  AND2X1 U102 ( .A(p2[5]), .B(p2[2]), .Y(n94) );
  NOR2BX1 U103 ( .AN(p2[3]), .B(n95), .Y(n84) );
  XNOR2X1 U104 ( .A(n90), .B(n96), .Y(c[2]) );
  XNOR2X1 U105 ( .A(n93), .B(n91), .Y(n96) );
  NAND2X1 U106 ( .A(p2[4]), .B(p2[2]), .Y(n91) );
  NOR3BXL U107 ( .AN(p2[1]), .B(n95), .C(n97), .Y(n93) );
  XOR2X1 U108 ( .A(n87), .B(n98), .Y(n90) );
  NOR2X1 U109 ( .A(n88), .B(n89), .Y(n98) );
  CLKINVX1 U110 ( .A(p2[6]), .Y(n88) );
  NAND2X1 U111 ( .A(p2[1]), .B(p2[5]), .Y(n87) );
  XOR2X1 U112 ( .A(n97), .B(n99), .Y(c[1]) );
  NAND2X1 U113 ( .A(p2[4]), .B(p2[1]), .Y(n99) );
  NAND2X1 U114 ( .A(p2[0]), .B(p2[5]), .Y(n97) );
  NOR2X1 U115 ( .A(n95), .B(n89), .Y(c[0]) );
  CLKINVX1 U116 ( .A(p2[0]), .Y(n89) );
  CLKINVX1 U117 ( .A(p2[4]), .Y(n95) );
endmodule

