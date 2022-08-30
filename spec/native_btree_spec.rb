# frozen_string_literal: true

RSpec.describe NativeBtree do
  it "has a version number" do
    expect(NativeBtree::VERSION).not_to be_nil
  end

  it "does something useful" do
    expect((1 + 1)).to be(2)
  end

  describe NativeBtree::Btree do
    it "respond to from" do
      expect(described_class.from).to be(10)
    end
  end
end
