require "mkmf"
require "rake"

abort "CMake build tool not found" unless find_executable('cmake')

File.open("Makefile", "wb") do |f|
  dummy_makefile(".").each do |line|
    f.puts(line)
  end
end

app = Rake.application
app.init
app.load_rakefile
app['cmake:rebuild'].invoke
