require 'spec_helper'
describe "integration" do
  context 'for  simple release presses' do
    context 'given a config file' do
      config_content =<<END
F1:a,00
F2:e,00
A2:b,00
A4:d,00
A1+F1:f,00
END
      config_file = "tmp/small"
      savef(config_file, config_content)

      context 'output the correct char' do
        it 'on simple quick press' do
          input_content =<<END
1000000000000000
0000000000000000
1111111111111111
END
          input_file = "tmp/input"
          savef(input_file, input_content)

          expected =<<END
38
END

          expect(`cat #{input_file} | ./spec/bin/ex1 #{config_file}`).to eq(expected)
        end

        it 'pressing longer before release' do
          input_content =<<END
1000000000000000
1000000000000000
1000000000000000
1000000000000000
1000000000000000
1000000000000000
0000000000000000
1111111111111111
END
          input_file = "tmp/input"
          savef(input_file, input_content)

          expected =<<END
38
END

          expect(`cat #{input_file} | ./spec/bin/ex1 #{config_file}`).to eq(expected)
        end
      end
    end
  end
end
