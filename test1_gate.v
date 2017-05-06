/////////////////////////////////////////////////////////////
// Created by: Synopsys DC Expert(TM) in wire load mode
// Version   : K-2015.06-SP3
// Date      : Sat May  6 22:39:18 2017
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


module test1 ( a, b, c, clk );
  input [7:0] a;
  input [7:0] b;
  output [7:0] c;
  input clk;

  wire   [7:0] next_p1;
  wire   [7:0] p1;
  wire   [7:0] next_p2;
  wire   [7:0] p2;

  test1_DW01_add_0 add_12 ( .A(a), .B(b), .CI(1'b0), .SUM(next_p1) );
  test1_DW_mult_uns_2 mult_16 ( .a(p1[3:0]), .b(p1[7:4]), .product(next_p2) );
  test1_DW_mult_uns_3 mult_19 ( .a(p2[3:0]), .b(p2[7:4]), .product(c) );
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
endmodule

