describe "integration" do
  context 'given a config file, output the correct char' do
    it 'for small sized file' do
      config_content =<<END
F1:a,00
F2:e,00
A2:b,00
A4:d,00
A1+F1:f,00
END
      config = "tmp/small"
      File.open(config, "w") do |file|
        file.write(config_content)
      end

      input_content =<<END
1000000000000000
0000000000000000
1111111111111111
END
      input = "tmp/input"
      File.open(input, "w") do |file|
        file.write(input_content)
      end

      expected =<<END
38
END

      expect(`cat tmp/input | ./spec/bin/ex1 #{config}`).to eq(expected)
    end
  end
end
