# frozen_string_literal: true

RSpec.describe NativeBtree do
  it "has a version number" do
    expect(described_class.const_defined?(:VERSION)).to be true
  end

  it "Has Btree contstant" do
    expect(described_class.const_defined?(:Btree)).to be true
  end

  it "Btree is class" do
    expect(described_class::Btree.class).to be Class
  end
end
