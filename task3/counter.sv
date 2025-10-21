//task 3.1:
/* module counter #(
    parameter WIDTH = 8
)(
    //interface signals
    input logic         clk,
    input logic         rst,
    input logic         ld,         //flag to load counter from data
    input logic [WIDTH-1:0] v,      //value to preload
    output logic [WIDTH-1:0] count
);


always_ff @ (posedge clk)
    if (rst) count <= {WIDTH{1'b0}};
    else     count <= ld ? count : count + {{WIDTH-1{1'b0}}, 1'b1};
endmodule */ 

//task 3.2:

module counter #(
    parameter WIDTH = 8
)(
    input  logic         clk,
    input  logic         rst,
    input  logic         ld,         // Vbuddy pushbutton
    input  logic [WIDTH-1:0] v,     // value to preload
    output logic [WIDTH-1:0] count
);

logic ld_d;  // delayed version of ld to detect edges

always_ff @(posedge clk) begin
    if (rst) begin
        count <= {WIDTH{1'b0}};
        ld_d   <= 0;
    end else begin
        ld_d <= ld; // store previous value
        // Increment only on rising edge of ld
        if (ld ^ ld_d) begin
            count <= count + 1;
        end
    end
end

endmodule

