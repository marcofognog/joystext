$: << '.'
require 'config_map'

f = File.open(".joystext","r").read
puts ConfigMap.translate(f)
