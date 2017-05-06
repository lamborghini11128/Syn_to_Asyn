module test1( a, b, c, clk, rst );
    input  [7:0] a;
    input  [7:0] b;
    input        clk;
    input        rst;
    output [7:0] c;

    reg    [7:0] p1, next_p1;
    reg    [7:0] p2, next_p2;
    reg    [7:0] counter, next_counter;

    always@(*) begin
        if( rst )
            next_counter = 8'd0;
        else
            next_counter = counter + 8'd1;
    end

    always@(*) begin
        next_p1 = a + b;
    end

    always@(*) begin
        next_p2 = { 4'b0, p1[3:0] } * { 4'b0, p1[7:4] }; 
    end

    assign c = p2 * counter;

    always@( posedge clk ) begin 
        p1 = next_p1;
        p2 = next_p2;
        counter = next_counter;
    end


endmodule