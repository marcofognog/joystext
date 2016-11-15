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
{{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},XK_a,0,0},
{{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},XK_e,0,0},
{{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},XK_b,0,0},
{{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},XK_d,0,0},
{{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},XK_f,0,0},
{{0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},XK_g,0,0},
{{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},XK_s,0,0},
{{0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0},XK_v,0,0},
{{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},XK_y,0,0},
{{0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0},XK_z,0,0},
{{0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,0},XK_comma,0,0},
{{1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0},XK_space,0,0},
{{1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0},XK_Super_L,XK_b,0},
{{0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,0},XK_Shift_L,XK_greater,0},
END

    `gcc -Wall -g parse_config.c -o parser`
    expect(`./parser #{file_name}`).to eq(expected)

  end
end
