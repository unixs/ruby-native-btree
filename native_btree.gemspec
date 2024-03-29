require_relative "lib/native_btree/version"

Gem::Specification.new do |s|
  s.name = 'native_btree'
  s.version = NativeBtree::VERSION

  s.metadata = {
    "bug_tracker_uri" => "https://github.com/unixs/ruby-native-btree/issues",
    "changelog_uri" => "https://github.com/unixs/ruby-native-btree/blob/master/CHANGELOG.md",
    "documentation_uri" => "https://github.com/unixs/ruby-native-btree/wiki",
    "homepage_uri" => "https://github.com/unixs/ruby-native-btree",
    "source_code_uri" => "https://github.com/unixs/ruby-native-btree",
    "wiki_uri" => "https://github.com/unixs/ruby-native-btree/wiki",
    "rubygems_mfa_required" => "true"
  }

  s.platform = Gem::Platform::RUBY
  s.summary = 'Balanced binary tree from GLib.'
  s.description = 'Ruby bindings to GTree balanced binary tree from GLib library.'
  s.authors = ['Alexander Feodorov']
  s.email = ['webmaster@unixcomp.org']
  s.licenses = ['LGPL-3.0-or-later']
  s.homepage = 'https://github.com/unixs/ruby-native-btree'
  s.extensions = ["ext/#{s.name}/extconf_cmake.rb"]

  s.files = Dir['{bin,ext,lib,spec}/**/*']
  s.files += Dir['*.{md}']
  s.files += %w[Rakefile Gemfile CMakeLists.txt native_btree.gemspec LICENSE]

  s.executables = s.files.grep(%r{\Abin/}) { |f| File.basename(f) }
  s.require_paths = ["lib"]
  s.required_ruby_version = '>= 2.6'
end
