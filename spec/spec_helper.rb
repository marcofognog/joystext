def savef(name, content)
  File.open(name, "w") do |file|
    file.write(content)
  end
end
