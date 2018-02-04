require 'redcarpet'

markdown = Redcarpet::Markdown.new Redcarpet::Render::HTML

unless ARGV.size == 2
    raise 'Usage: mdparse input.file output.file'
end

if File.exists?(ARGV[0])
    input_file = File.open ARGV[0], "r"
else
    raise 'Could not read input file'
end

input = input_file.read

output_file = File.open ARGV[1], "w"

output = markdown.render input

output = output.gsub(/<code>.*\n(.)/, '<code>\1')

output_file.write output