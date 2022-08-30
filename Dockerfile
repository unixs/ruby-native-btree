FROM unixs/ruby-cmake:2.7

RUN mkdir -p /home/gem
WORKDIR /home/gem
COPY . .
RUN gem install bundler && \
  bundle config set deployment true && \
  bundle install && \
  rake spec && \
  gem install pkg/native_btree-0.1.0.alpha1.gem
