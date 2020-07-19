require 'rake'
require_relative "lib/native_btree/version"

spec = Gem::Specification.new do |s|
  s.name = 'native_btree'.freeze
  s.version = NativeBTree::VERSION

  s.platform = Gem::Platform::RUBY
  s.date = '2020-07-11'.freeze
  s.summary = 'Bindings to GTree data stucture from libglib-2.0'.freeze
  s.authors = ['Alexander Feodorov'.freeze]
  s.email = ['webmaster@unixcomp.org'.freeze]
  s.licenses = ['MIT'.freeze]
  s.homepage = 'https://github.com/unixs/ruby-native-btree'.freeze
  s.extensions = FileList["ext/**/extconf.rb".freeze]
  s.files = FileList['lib/**/*.rb', 'ext/**/*.{rb,c,h,cc}'.freeze]
  s.require_paths = ['lib'.freeze]
  s.required_ruby_version = '>= 2.5'
end
