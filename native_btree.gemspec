require "file_utils"
require File.expand_path("../lib/native_btree/version", __FILE__)

spec = Gem::Specification.new do |s|
  s.name = 'native_btree'.freeze
  s.version = NativeBTree::VERSION

  s.platform = Gem::Platform::RUBY
  s.date = '2020-07-11'.freeze
  s.summary = 'Bindings to GTree data stucture from libglib.'.freeze
  s.authors = ['Alexander Feodorov'.freeze]
  s.email = ['webmaster@unixcomp.org'.freeze]
  s.licenses = ['MIT'.freeze]
  s.homepage = 'https://github.com/unixs/ruby-native-btree'.freeze
  s.extensions = FileList["ext/**/extconf.rb".freeze]
  s.files = [
    'ext/native_btree/native_btree.cc'.freeze,
    'lib/native_btree.rb'.freeze,
    'lib/native_btree/version.rb'.freeze
  ]
  s.require_paths = ['lib'.freeze]
end

Rake::ExtensionTask.new('native_btree', spec)
