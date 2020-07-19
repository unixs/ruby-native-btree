require 'rake'
require_relative "lib/native_btree/version"

spec = Gem::Specification.new do |s|
  s.name = 'native_btree'.freeze
  s.version = NativeBTree::VERSION

  s.platform = Gem::Platform::RUBY
  s.date = '2020-07-11'.freeze
  s.summary = 'Balanced binary tree from GLib.'.freeze
  s.description = 'Ruby bindings to GTree balanced binary tree from GLib library.'.freeze
  s.authors = ['Alexander Feodorov'.freeze]
  s.email = ['webmaster@unixcomp.org'.freeze]
  s.licenses = ['MIT'.freeze]
  s.homepage = 'https://github.com/unixs/ruby-native-btree'.freeze
  s.extensions = FileList["ext/**/extconf.rb".freeze]
  s.files = FileList['lib/**/*.rb', 'ext/**/*.{rb,c,h,cc}'.freeze]
  s.require_paths = ['lib'.freeze]
  s.required_ruby_version = '>= 2.5'

  s.add_development_dependency 'solargraph'
  s.add_development_dependency 'ruby-debug-ide'
  s.add_development_dependency 'debase'
  s.add_development_dependency 'pry'
  s.add_development_dependency 'awesome_print'
end
