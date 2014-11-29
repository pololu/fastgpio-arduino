# Ruby script to help generate the FastGPIO library code.

class PinConfig
  attr_reader :name
  attr_reader :pin_list

  def initialize(pin_list_str)
    @pin_list = pin_list_str.split.map { |s| { port: s[0], bit: s[1].to_i } }
  end

  def macros
    h = {}
    each_pin do |num, port, bit|
      h["IO_#{port}#{bit}"] = num
    end
    h
  end

  def macro_definitions
    r = ''
    macros.each do |name, num|
      r << "#define #{name} #{num}\n"
    end
    r
  end

  def array
    r = ''
    r << "    const IOStruct pinStructs[] = {\n"
    each_pin do |num, port, bit|
      r << "        _FG_PIN(#{port}, #{bit}),\n"
    end
    r << "    };"
    r
  end

  def table
    r = ''
    r << <<END
<table>
<tr><th>Number</th><th>AVR pin macro</th><th>Alternative name</th></tr>
END
    each_pin do |num, port, bit|
      r << "<tr><td>#{num}</td><td>IO_#{port}#{bit}</td><td></td></tr>\n"
    end
    r << '</table>'
    r
  end

  def each_pin
    @pin_list.each_with_index do |pin, num|
      yield num, pin.fetch(:port), pin.fetch(:bit)
    end
  end
end

def keywords(pin_configs)
  r = ''
  pin_keywords = pin_configs.flat_map { |c| c.macros.keys }.uniq.sort
  pin_keywords.each do |pin_keyword|
    r << (pin_keyword + "\tLITERAL1\n")
  end
  r << "IO_NONE\tLITERAL1\n"
  r
end

leonardo = PinConfig.new <<END
D2
D3
D1
D0
D4
C6
D7
E6
B4
B5
B6
B7
D6
C7
B3
B1
B2
B0
F7
F6
F5
F4
F1
F0
D4
D7
B4
B5
B6
D6
D5
E2
E0
END

uno = PinConfig.new <<END
D0
D1
D2
D3
D4
D5
D6
D7
B0
B1
B2
B3
B4
B5
C0
C1
C2
C3
C4
C5
C6
C7
END

#puts leonardo.macros
#puts uno.table
#puts leonardo.table

puts keywords([leonardo, uno])
