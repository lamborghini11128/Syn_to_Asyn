/////////////////////////////////////////////////////////////
// Created by: Synopsys DC Expert(TM) in wire load mode
// Version   : K-2015.06-SP3
// Date      : Sat May  6 22:49:56 2017
/////////////////////////////////////////////////////////////


module test1_DW01_add_0 ( A, B, CI, SUM, CO );
  input [7:0] A;
  input [7:0] B;
  output [7:0] SUM;
  input CI;
  output CO;
  wire   n1;
  wire   [7:1] carry;

  XOR3X1 U1_7 ( .A(A[7]), .B(B[7]), .C(carry[7]), .Y(SUM[7]) );
  ADDFXL U1_6 ( .A(A[6]), .B(B[6]), .CI(carry[6]), .CO(carry[7]), .S(SUM[6])
         );
  ADDFXL U1_5 ( .A(A[5]), .B(B[5]), .CI(carry[5]), .CO(carry[6]), .S(SUM[5])
         );
  ADDFXL U1_4 ( .A(A[4]), .B(B[4]), .CI(carry[4]), .CO(carry[5]), .S(SUM[4])
         );
  ADDFXL U1_3 ( .A(A[3]), .B(B[3]), .CI(carry[3]), .CO(carry[4]), .S(SUM[3])
         );
  ADDFXL U1_2 ( .A(A[2]), .B(B[2]), .CI(carry[2]), .CO(carry[3]), .S(SUM[2])
         );
  ADDFXL U1_1 ( .A(A[1]), .B(B[1]), .CI(n1), .CO(carry[2]), .S(SUM[1]) );
  AND2X2 U1 ( .A(B[0]), .B(A[0]), .Y(n1) );
  XOR2X1 U2 ( .A(B[0]), .B(A[0]), .Y(SUM[0]) );
endmodule


module test1_DW01_inc_0 ( A, SUM );
  input [7:0] A;
  output [7:0] SUM;

  wire   [7:2] carry;

  ADDHXL U1_1_6 ( .A(A[6]), .B(carry[6]), .CO(carry[7]), .S(SUM[6]) );
  ADDHXL U1_1_5 ( .A(A[5]), .B(carry[5]), .CO(carry[6]), .S(SUM[5]) );
  ADDHXL U1_1_4 ( .A(A[4]), .B(carry[4]), .CO(carry[5]), .S(SUM[4]) );
  ADDHXL U1_1_3 ( .A(A[3]), .B(carry[3]), .CO(carry[4]), .S(SUM[3]) );
  ADDHXL U1_1_2 ( .A(A[2]), .B(carry[2]), .CO(carry[3]), .S(SUM[2]) );
  ADDHXL U1_1_1 ( .A(A[1]), .B(A[0]), .CO(carry[2]), .S(SUM[1]) );
  XOR2X1 U1 ( .A(carry[7]), .B(A[7]), .Y(SUM[7]) );
  CLKINVX1 U2 ( .A(A[0]), .Y(SUM[0]) );
endmodule


module test1_DW_mult_uns_2 ( a, b, product );
  input [3:0] a;
  input [3:0] b;
  output [7:0] product;
  wire   n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14, n15, n16,
         n17, n18, n19, n20, n21, n22, n23, n24, n25, n26, n27, n28, n29, n30,
         n31, n32, n33, n34, n35, n36, n37, n38, n39, n40, n41;
  assign product[7] = n1;

  ADDFXL U2 ( .A(n7), .B(n19), .CI(n2), .CO(n1), .S(product[6]) );
  ADDFXL U3 ( .A(n9), .B(n8), .CI(n3), .CO(n2), .S(product[5]) );
  ADDFXL U4 ( .A(n10), .B(n13), .CI(n4), .CO(n3), .S(product[4]) );
  ADDFXL U5 ( .A(n14), .B(n16), .CI(n5), .CO(n4), .S(product[3]) );
  ADDFXL U6 ( .A(n6), .B(n26), .CI(n18), .CO(n5), .S(product[2]) );
  ADDHXL U7 ( .A(n30), .B(n33), .CO(n6), .S(product[1]) );
  ADDFXL U8 ( .A(n20), .B(n23), .CI(n11), .CO(n7), .S(n8) );
  ADDFXL U9 ( .A(n15), .B(n24), .CI(n12), .CO(n9), .S(n10) );
  ADDHXL U10 ( .A(n27), .B(n21), .CO(n11), .S(n12) );
  ADDFXL U11 ( .A(n28), .B(n31), .CI(n17), .CO(n13), .S(n14) );
  ADDHXL U12 ( .A(n25), .B(n22), .CO(n15), .S(n16) );
  ADDHXL U13 ( .A(n32), .B(n29), .CO(n17), .S(n18) );
  NOR2X1 U14 ( .A(n34), .B(n38), .Y(n19) );
  NOR2X1 U15 ( .A(n35), .B(n38), .Y(n20) );
  NOR2X1 U16 ( .A(n36), .B(n38), .Y(n21) );
  NOR2X1 U17 ( .A(n37), .B(n38), .Y(n22) );
  NOR2X1 U18 ( .A(n34), .B(n39), .Y(n23) );
  NOR2X1 U19 ( .A(n35), .B(n39), .Y(n24) );
  NOR2X1 U20 ( .A(n36), .B(n39), .Y(n25) );
  NOR2X1 U21 ( .A(n37), .B(n39), .Y(n26) );
  NOR2X1 U22 ( .A(n34), .B(n40), .Y(n27) );
  NOR2X1 U23 ( .A(n35), .B(n40), .Y(n28) );
  NOR2X1 U24 ( .A(n36), .B(n40), .Y(n29) );
  NOR2X1 U25 ( .A(n37), .B(n40), .Y(n30) );
  NOR2X1 U26 ( .A(n34), .B(n41), .Y(n31) );
  NOR2X1 U27 ( .A(n35), .B(n41), .Y(n32) );
  NOR2X1 U28 ( .A(n36), .B(n41), .Y(n33) );
  NOR2X1 U29 ( .A(n37), .B(n41), .Y(product[0]) );
  CLKINVX1 U40 ( .A(b[0]), .Y(n37) );
  CLKINVX1 U41 ( .A(b[1]), .Y(n36) );
  CLKINVX1 U42 ( .A(b[3]), .Y(n34) );
  CLKINVX1 U43 ( .A(b[2]), .Y(n35) );
  CLKINVX1 U44 ( .A(a[1]), .Y(n40) );
  CLKINVX1 U45 ( .A(a[3]), .Y(n38) );
  CLKINVX1 U46 ( .A(a[0]), .Y(n41) );
  CLKINVX1 U47 ( .A(a[2]), .Y(n39) );
endmodule


module test1_DW_mult_uns_3 ( a, b, product );
  input [7:0] a;
  input [7:0] b;
  output [15:0] product;
  wire   n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14, n15, n16,
         n17, n18, n19, n20, n21, n22, n23, n24, n25, n26, n27, n28, n29, n30,
         n31, n32, n33, n34, n35, n36, n37, n38, n39, n40, n41, n42, n43, n44,
         n45, n46, n47, n48, n49, n50, n51, n52, n53, n54, n55, n56, n57, n58,
         n59, n60, n61, n62, n63, n64, n65, n66, n67, n68, n69, n70, n71, n72,
         n73, n74, n75, n76, n77, n78, n79, n80, n81, n82, n83, n84, n85, n86,
         n87, n88, n89, n90, n91, n92, n93, n94;

  XOR2X1 U1 ( .A(n2), .B(n1), .Y(product[7]) );
  XOR2X1 U2 ( .A(n11), .B(n19), .Y(n1) );
  ADDFXL U3 ( .A(n20), .B(n27), .CI(n3), .CO(n2), .S(product[6]) );
  ADDFXL U4 ( .A(n28), .B(n34), .CI(n4), .CO(n3), .S(product[5]) );
  ADDFXL U5 ( .A(n35), .B(n38), .CI(n5), .CO(n4), .S(product[4]) );
  ADDFXL U6 ( .A(n39), .B(n41), .CI(n6), .CO(n5), .S(product[3]) );
  ADDFXL U7 ( .A(n7), .B(n64), .CI(n43), .CO(n6), .S(product[2]) );
  ADDHXL U8 ( .A(n71), .B(n78), .CO(n7), .S(product[1]) );
  XOR2X1 U9 ( .A(n8), .B(n10), .Y(n11) );
  XOR2X1 U10 ( .A(n15), .B(n22), .Y(n8) );
  XOR2X1 U11 ( .A(n18), .B(n9), .Y(n10) );
  XOR2X1 U12 ( .A(n21), .B(n54), .Y(n9) );
  XOR2X1 U13 ( .A(n12), .B(n14), .Y(n15) );
  XOR2X1 U14 ( .A(n16), .B(n24), .Y(n12) );
  XOR2X1 U15 ( .A(n13), .B(n59), .Y(n14) );
  XOR2X1 U16 ( .A(n50), .B(n65), .Y(n13) );
  XOR3X1 U17 ( .A(n72), .B(n47), .C(n17), .Y(n16) );
  XOR2X1 U18 ( .A(n44), .B(n45), .Y(n17) );
  CMPR42X1 U19 ( .A(n60), .B(n55), .C(n26), .D(n29), .ICI(n23), .S(n20), .ICO(
        n18), .CO(n19) );
  CMPR42X1 U20 ( .A(n73), .B(n51), .C(n66), .D(n31), .ICI(n25), .S(n23), .ICO(
        n21), .CO(n22) );
  ADDHXL U21 ( .A(n48), .B(n46), .CO(n24), .S(n25) );
  CMPR42X1 U22 ( .A(n61), .B(n67), .C(n32), .D(n33), .ICI(n30), .S(n28), .ICO(
        n26), .CO(n27) );
  ADDFXL U23 ( .A(n56), .B(n74), .CI(n36), .CO(n29), .S(n30) );
  ADDHXL U24 ( .A(n52), .B(n49), .CO(n31), .S(n32) );
  CMPR42X1 U25 ( .A(n75), .B(n62), .C(n68), .D(n40), .ICI(n37), .S(n35), .ICO(
        n33), .CO(n34) );
  ADDHXL U26 ( .A(n57), .B(n53), .CO(n36), .S(n37) );
  ADDFXL U27 ( .A(n69), .B(n76), .CI(n42), .CO(n38), .S(n39) );
  ADDHXL U28 ( .A(n63), .B(n58), .CO(n40), .S(n41) );
  ADDHXL U29 ( .A(n77), .B(n70), .CO(n42), .S(n43) );
  NOR2X1 U30 ( .A(n86), .B(n87), .Y(n44) );
  NOR2X1 U31 ( .A(n85), .B(n88), .Y(n45) );
  NOR2X1 U32 ( .A(n86), .B(n88), .Y(n46) );
  NOR2X1 U33 ( .A(n84), .B(n89), .Y(n47) );
  NOR2X1 U34 ( .A(n85), .B(n89), .Y(n48) );
  NOR2X1 U35 ( .A(n86), .B(n89), .Y(n49) );
  NOR2X1 U36 ( .A(n83), .B(n90), .Y(n50) );
  NOR2X1 U37 ( .A(n84), .B(n90), .Y(n51) );
  NOR2X1 U38 ( .A(n85), .B(n90), .Y(n52) );
  NOR2X1 U39 ( .A(n86), .B(n90), .Y(n53) );
  NOR2X1 U40 ( .A(n82), .B(n91), .Y(n54) );
  NOR2X1 U41 ( .A(n83), .B(n91), .Y(n55) );
  NOR2X1 U42 ( .A(n84), .B(n91), .Y(n56) );
  NOR2X1 U43 ( .A(n85), .B(n91), .Y(n57) );
  NOR2X1 U44 ( .A(n86), .B(n91), .Y(n58) );
  NOR2X1 U45 ( .A(n81), .B(n92), .Y(n59) );
  NOR2X1 U46 ( .A(n82), .B(n92), .Y(n60) );
  NOR2X1 U47 ( .A(n83), .B(n92), .Y(n61) );
  NOR2X1 U48 ( .A(n84), .B(n92), .Y(n62) );
  NOR2X1 U49 ( .A(n85), .B(n92), .Y(n63) );
  NOR2X1 U50 ( .A(n86), .B(n92), .Y(n64) );
  NOR2X1 U51 ( .A(n80), .B(n93), .Y(n65) );
  NOR2X1 U52 ( .A(n81), .B(n93), .Y(n66) );
  NOR2X1 U53 ( .A(n82), .B(n93), .Y(n67) );
  NOR2X1 U54 ( .A(n83), .B(n93), .Y(n68) );
  NOR2X1 U55 ( .A(n84), .B(n93), .Y(n69) );
  NOR2X1 U56 ( .A(n85), .B(n93), .Y(n70) );
  NOR2X1 U57 ( .A(n86), .B(n93), .Y(n71) );
  NOR2X1 U58 ( .A(n79), .B(n94), .Y(n72) );
  NOR2X1 U59 ( .A(n80), .B(n94), .Y(n73) );
  NOR2X1 U60 ( .A(n81), .B(n94), .Y(n74) );
  NOR2X1 U61 ( .A(n82), .B(n94), .Y(n75) );
  NOR2X1 U62 ( .A(n83), .B(n94), .Y(n76) );
  NOR2X1 U63 ( .A(n84), .B(n94), .Y(n77) );
  NOR2X1 U64 ( .A(n85), .B(n94), .Y(n78) );
  NOR2X1 U65 ( .A(n86), .B(n94), .Y(product[0]) );
  CLKINVX1 U84 ( .A(a[7]), .Y(n87) );
  CLKINVX1 U85 ( .A(b[0]), .Y(n86) );
  CLKINVX1 U86 ( .A(b[1]), .Y(n85) );
  CLKINVX1 U87 ( .A(a[0]), .Y(n94) );
  CLKINVX1 U88 ( .A(b[2]), .Y(n84) );
  CLKINVX1 U89 ( .A(a[1]), .Y(n93) );
  CLKINVX1 U90 ( .A(b[3]), .Y(n83) );
  CLKINVX1 U91 ( .A(a[2]), .Y(n92) );
  CLKINVX1 U92 ( .A(b[4]), .Y(n82) );
  CLKINVX1 U93 ( .A(a[3]), .Y(n91) );
  CLKINVX1 U94 ( .A(b[5]), .Y(n81) );
  CLKINVX1 U95 ( .A(a[4]), .Y(n90) );
  CLKINVX1 U96 ( .A(b[6]), .Y(n80) );
  CLKINVX1 U97 ( .A(a[5]), .Y(n89) );
  CLKINVX1 U98 ( .A(a[6]), .Y(n88) );
  CLKINVX1 U99 ( .A(b[7]), .Y(n79) );
endmodule


module test1 ( a, b, c, clk, rst );
  input [7:0] a;
  input [7:0] b;
  output [7:0] c;
  input clk, rst;
  wire   N3, N4, N5, N6, N7, N8, N9, N10;
  wire   [7:0] next_counter;
  wire   [7:0] counter;
  wire   [7:0] next_p1;
  wire   [7:0] p1;
  wire   [7:0] next_p2;
  wire   [7:0] p2;
  wire   SYNOPSYS_UNCONNECTED__0, SYNOPSYS_UNCONNECTED__1, 
        SYNOPSYS_UNCONNECTED__2, SYNOPSYS_UNCONNECTED__3, 
        SYNOPSYS_UNCONNECTED__4, SYNOPSYS_UNCONNECTED__5, 
        SYNOPSYS_UNCONNECTED__6, SYNOPSYS_UNCONNECTED__7;

  test1_DW01_add_0 add_20 ( .A(a), .B(b), .CI(1'b0), .SUM(next_p1) );
  test1_DW01_inc_0 add_16 ( .A(counter), .SUM({N10, N9, N8, N7, N6, N5, N4, N3}) );
  test1_DW_mult_uns_2 mult_24 ( .a(p1[3:0]), .b(p1[7:4]), .product(next_p2) );
  test1_DW_mult_uns_3 mult_27 ( .a(p2), .b(counter), .product({
        SYNOPSYS_UNCONNECTED__0, SYNOPSYS_UNCONNECTED__1, 
        SYNOPSYS_UNCONNECTED__2, SYNOPSYS_UNCONNECTED__3, 
        SYNOPSYS_UNCONNECTED__4, SYNOPSYS_UNCONNECTED__5, 
        SYNOPSYS_UNCONNECTED__6, SYNOPSYS_UNCONNECTED__7, c}) );
  DFFQX1 \p1_reg[7]  ( .D(next_p1[7]), .CK(clk), .Q(p1[7]) );
  DFFQX1 \p1_reg[6]  ( .D(next_p1[6]), .CK(clk), .Q(p1[6]) );
  DFFQX1 \p1_reg[5]  ( .D(next_p1[5]), .CK(clk), .Q(p1[5]) );
  DFFQX1 \p1_reg[4]  ( .D(next_p1[4]), .CK(clk), .Q(p1[4]) );
  DFFQX1 \p1_reg[3]  ( .D(next_p1[3]), .CK(clk), .Q(p1[3]) );
  DFFQX1 \p1_reg[2]  ( .D(next_p1[2]), .CK(clk), .Q(p1[2]) );
  DFFQX1 \p1_reg[1]  ( .D(next_p1[1]), .CK(clk), .Q(p1[1]) );
  DFFQX1 \p1_reg[0]  ( .D(next_p1[0]), .CK(clk), .Q(p1[0]) );
  DFFQX1 \p2_reg[7]  ( .D(next_p2[7]), .CK(clk), .Q(p2[7]) );
  DFFQX1 \p2_reg[6]  ( .D(next_p2[6]), .CK(clk), .Q(p2[6]) );
  DFFQX1 \p2_reg[5]  ( .D(next_p2[5]), .CK(clk), .Q(p2[5]) );
  DFFQX1 \p2_reg[4]  ( .D(next_p2[4]), .CK(clk), .Q(p2[4]) );
  DFFQX1 \p2_reg[3]  ( .D(next_p2[3]), .CK(clk), .Q(p2[3]) );
  DFFQX1 \p2_reg[2]  ( .D(next_p2[2]), .CK(clk), .Q(p2[2]) );
  DFFQX1 \p2_reg[1]  ( .D(next_p2[1]), .CK(clk), .Q(p2[1]) );
  DFFQX1 \p2_reg[0]  ( .D(next_p2[0]), .CK(clk), .Q(p2[0]) );
  DFFQX1 \counter_reg[7]  ( .D(next_counter[7]), .CK(clk), .Q(counter[7]) );
  DFFQX1 \counter_reg[0]  ( .D(next_counter[0]), .CK(clk), .Q(counter[0]) );
  DFFQX1 \counter_reg[1]  ( .D(next_counter[1]), .CK(clk), .Q(counter[1]) );
  DFFQX1 \counter_reg[2]  ( .D(next_counter[2]), .CK(clk), .Q(counter[2]) );
  DFFQX1 \counter_reg[3]  ( .D(next_counter[3]), .CK(clk), .Q(counter[3]) );
  DFFQX1 \counter_reg[4]  ( .D(next_counter[4]), .CK(clk), .Q(counter[4]) );
  DFFQX1 \counter_reg[5]  ( .D(next_counter[5]), .CK(clk), .Q(counter[5]) );
  DFFQX1 \counter_reg[6]  ( .D(next_counter[6]), .CK(clk), .Q(counter[6]) );
  NOR2BX1 U12 ( .AN(N10), .B(rst), .Y(next_counter[7]) );
  NOR2BX1 U13 ( .AN(N9), .B(rst), .Y(next_counter[6]) );
  NOR2BX1 U14 ( .AN(N8), .B(rst), .Y(next_counter[5]) );
  NOR2BX1 U15 ( .AN(N7), .B(rst), .Y(next_counter[4]) );
  NOR2BX1 U16 ( .AN(N6), .B(rst), .Y(next_counter[3]) );
  NOR2BX1 U17 ( .AN(N5), .B(rst), .Y(next_counter[2]) );
  NOR2BX1 U18 ( .AN(N4), .B(rst), .Y(next_counter[1]) );
  NOR2BX1 U19 ( .AN(N3), .B(rst), .Y(next_counter[0]) );
endmodule

