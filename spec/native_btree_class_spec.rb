# frozen_string_literal: true

RSpec.describe NativeBtree do
  it "has a version number" do
    expect(NativeBtree::VERSION).not_to be_nil
  end

  describe NativeBtree::Btree do

    describe "initialize class method" do
      it 'respond to new' do
        expect(described_class).to respond_to('new').with(0).arguments
      end

      it "return new btree instance" do
        expect(described_class.new { nil }).to be_kind_of(described_class)
      end

      it "raise error if block is not given" do
        expect { described_class.new() }.to raise_error(LocalJumpError)
      end
    end
  end
end
