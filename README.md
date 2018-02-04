# CLog gh-pages

This is the README for the GitHub Page for CLog.

## Requirements

To install the requirements, `bundle install`.

## Workflow

Every tag's code will be copied into `code`, and the various documentation will
be parsed using RedCarpet. This text will be (for now) manually copied into the
respective files. If the CSS has changed, compile the Sass into `site.css`.

### Compiling Sass

```sh
$ sass src/sass/application.sass site.css
or
$ sass --watch src/sass/application.sass:site.css > log/sass &
```

### Parsing Markdown with RedCarpet

```sh
$ ruby scripts/mdparse.rb input.md output.html
```

The `output.html` must be manually copied to its destination. (Until HTMLPp is
functional)
