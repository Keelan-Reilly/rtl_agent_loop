package types_pkg;
  // Architecture encodings are kept in one place so RTL, scripts, and docs
  // can refer to the same stable integer values.
  localparam int ARCH_BASELINE   = 0;
  localparam int ARCH_SHARED     = 1;
  localparam int ARCH_REPLICATED = 2;

  typedef logic signed [15:0] data16_t;
  typedef logic signed [31:0] acc32_t;

  function automatic int ceil_div(input int numerator, input int denominator);
    if (denominator <= 0) begin
      return 0;
    end
    return (numerator + denominator - 1) / denominator;
  endfunction

  function automatic int max_int(input int lhs, input int rhs);
    return (lhs > rhs) ? lhs : rhs;
  endfunction

  function automatic int safe_clog2(input int value);
    if (value <= 1) begin
      return 1;
    end
    return $clog2(value);
  endfunction

  function automatic string arch_variant_name(input int arch_variant);
    case (arch_variant)
      ARCH_BASELINE:   return "baseline";
      ARCH_SHARED:     return "shared";
      ARCH_REPLICATED: return "replicated";
      default:         return "unknown";
    endcase
  endfunction
endpackage
