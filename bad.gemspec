# frozen_string_literal: true

require_relative "lib/bad/version"

Gem::Specification.new do |spec|
	spec.name = "bad"
	spec.version = Bad::VERSION
	
	spec.summary = "Test bad things."
	spec.authors = ["Samuel Williams"]
	spec.license = "MIT"
	
	spec.cert_chain  = ["release.cert"]
	spec.signing_key = File.expand_path("~/.gem/release.pem")
	
	spec.homepage = "https://github.com/ioquatix/bad"
	
	spec.metadata = {
		"documentation_uri" => "https://ioquatix.github.io/bad/",
		"funding_uri" => "https://github.com/sponsors/ioquatix/",
		"source_code_uri" => "https://github.com/ioquatix/bad.git",
	}
	
	spec.files = Dir.glob(["{lib}/**/*", "{ext}/**/*.{c,h,rb}", "*.md"], File::FNM_DOTMATCH, base: __dir__)
	
	spec.required_ruby_version = ">= 3.1"
	
	spec.extensions = ["ext/extconf.rb"]
end
