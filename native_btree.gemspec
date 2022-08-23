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
  s.licenses = ['LGPLv3']
  s.homepage = 'https://github.com/unixs/ruby-native-btree'
  # s.extensions = FileList["ext/**/extconf.rb"]
  # Specify which files should be added to the gem when it is released.
  # The `git ls-files -z` loads the files in the RubyGem that have been added into git.
  s.files = Dir.chdir(__dir__) do
    `git ls-files -z`.split("\x0").reject do |f|
      (f == __FILE__) || f.match(%r{\A(?:(?:bin|test|spec|features)/|\.(?:git|travis|circleci)|appveyor)})
    end
  end
  s.bindir = "bin"
  s.executables = s.files.grep(%r{\Aexe/}) { |f| File.basename(f) }
  s.require_paths = ["lib"]
  s.required_ruby_version = '>= 2.6'

  s.add_development_dependency 'awesome_print'
  s.add_development_dependency 'debase'
  s.add_development_dependency 'pry'
  s.add_development_dependency 'ruby-debug-ide'
  s.add_development_dependency 'solargraph'
  s.add_development_dependency 'rubocop'
  s.add_development_dependency 'rubocop-rake'
  s.add_development_dependency 'rubocop-rspec'
  s.add_development_dependency 'rake'
  s.add_development_dependency 'rspec'
end
