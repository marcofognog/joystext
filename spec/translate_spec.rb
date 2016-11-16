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
A1+F3+F4:comma
A1+F4+F1:space

S1+A1+F1:super+b
S1+A1+F2:greater
END

file_name = "tmp/source"
File.open(file_name, "w") do |file|
  file.write(config)
end
    expected =<<END
1000000000000000,XK_a,0,0
0100000000000000,XK_e,0,0
0000000000000100,XK_b,0,0
0000000000001000,XK_d,0,0
1000000000000010,XK_f,0,0
0100000000000010,XK_g,0,0
0001000000000001,XK_s,0,0
0100000000001000,XK_v,0,0
1100000000000010,XK_y,0,0
0110000000000010,XK_z,0,0
0011000000000010,XK_comma,0,0
1001000000000010,XK_space,0,0
1000100000000010,XK_Super_L,XK_b,0
0100100000000010,XK_Shift_L,XK_greater,0
END

    `rm parser`
    `gcc -std=c99 -Wall -g -I/usr/include/SDL2/ parse_config.c -L/usr/local/lib/ -lSDL -lXtst -lX11 -o parser`
    expect(`./parser #{file_name}`).to eq(expected)

  end
end
