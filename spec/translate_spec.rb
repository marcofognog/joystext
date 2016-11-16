require 'spec_helper.rb'

describe ConfigMap do
  it 'translate' do
    config =<<END
F1:a
F2:e
A2:b
A4:d

A1+F1:f
A1+F2:g
A3+F4:s
A4+F2:v

A1+F1+F2:y
A1+F2+F3:z
END

file_name = "tmp/source"
File.open(file_name, "w") do |file|
  file.write(config)
end
    expected =<<END
1000000000000000
0100000000000000
0000000000000100
0000000000001000
1000000000000010
0100000000000010
0001000000000001
0100000000001000
1100000000000010
0110000000000010
END

    `rm parser`
    `gcc -Wall -std=c99 -g parse_config.c -o parser`
    expect(`./parser #{file_name}`).to eq(expected)

  end
end
