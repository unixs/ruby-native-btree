require 'rake/extensiontask'

GEMSPEC = Gem::Specification.load("native_btree.gemspec")

# add your default gem packing task
Gem::PackageTask.new(GEMSPEC) do |pkg|
end

Rake::ExtensionTask.new 'native_btree', GEMSPEC do |ext|
  ext.lib_dir = "lib/native_btree"
end
