require 'spec_helper.rb'

def build
  `rm tester`
  `gcc -std=c99 -Wall -g -I/usr/include/SDL2/ tester.c -L/usr/local/lib/ -lSDL -lXtst -lX11 -o tester`
end

describe ConfigMap do
  context 'transforms the config file keybindings into the binary version' do
    it 'for medium sized file' do
      config =<<END
F1:a
F2:e
A2:b
A4:d
A1+F1:f
END
      file_name = "tmp/source1"
      File.open(file_name, "w") do |file|
        file.write(config)
      end

      expected =<<END
1000000000000000,97,0,0
0100000000000000,101,0,0
0000000000000100,98,0,0
0000000000001000,100,0,0
1000000000000010,102,0,0
END
      build
      expect(`./tester #{file_name}`).to eq(expected)
    end

    it 'for medium sized file' do
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

S3+A1+F1:super+b
S4+A1+F2:greater
select:c

S4+A1+F2+F3:equal
S1+S2+S3+S4:double_quote
END

      file_name = "tmp/source"
      File.open(file_name, "w") do |file|
        file.write(config)
      end
      expected =<<END
1000000000000000,97,0,0
0100000000000000,101,0,0
0000000000000100,98,0,0
0000000000001000,100,0,0
1000000000000010,102,0,0
0100000000000010,103,0,0
0001000000000001,115,0,0
0100000000001000,118,0,0
1100000000000010,121,0,0
0110000000000010,122,0,0
0011000000000010,44,0,0
1001000000000010,32,0,0
1000010000000010,65515,98,0
0100000100000010,65505,62,0
0000000010000000,99,0,0
0110000100000010,61,0,0
0000111100000000,65505,34,0
END

      build
      expect(`./tester #{file_name}`).to eq(expected)
    end
  end
end
