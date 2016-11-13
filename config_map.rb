class ConfigMap
  MAP = {
    "F1" => "1000000000000000",
    "F2" => "0100000000000000",
    "F3" => "0010000000000000",
    "F4" => "0001000000000000",
    "A1" => "0000000000000010",
    "A2" => "0000000000000100",
    "A3" => "0000000000000001",
    "A4" => "0000000000001000",
    "S1" => "0000100000000000",
    "S2" => "0000001000000000",
    "S3" => "0000010000000000",
    "S4" => "0000000100000000",
    "select" => "0000000010000000",
    "start" => "0000000001000000",
    "C1" => "0000000000100000",
    "C2" => "0000000000010000"
  }

  def self.merge(a, b)
    result = []
    a.split("").each_with_index do |el,i|
      result[i.to_i] = ((a[i] == "1") || (b[i] == "1")) ? "1" : "0"
    end
    result.join
  end

  def self.translate(config_text)
    result_lines = []
    config_text.each_line do |line|
      if line.split("\n").any?
        signifier = line.split(":").first
        signified = line.split(":").last.gsub("\n","")

        binaries = signifier.split("+").map do |sig|
          unless sig == "\n"
            MAP[sig]
          end
        end.compact

        merged = "0000000000000000"
        binaries.each do |bin|
          merged = merge(bin, merged)
        end
        result_lines << "int #{signified}[16] = {" + merged.split("").join(",") + "};\n"
      end
    end
    result_lines.join
  end
end

