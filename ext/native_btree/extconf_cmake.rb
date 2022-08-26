require "mkmf"
require "rake"

abort "CMake build tool not found" unless find_executable('cmake')

# dummy_makefile('native_btree/native_btree')
create_makefile "native_btree/native_btree"

app = Rake.application
app.init
app.load_rakefile
app['cmake:build'].invoke
