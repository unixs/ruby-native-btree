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

  it "Has Glib contstant" do
    expect(described_class.const_defined?(:Glib)).to be true
  end

  it "Glib is module" do
    expect(described_class::Glib.class).to be Module
  end

  it "Has MAJOR_VERSION contstant" do
    expect(described_class::Glib.const_defined?(:MAJOR_VERSION)).to be true
  end

  it "Has MINOR_VERSION contstant" do
    expect(described_class::Glib.const_defined?(:MINOR_VERSION)).to be true
  end

  it "Has MICRO_VERSION contstant" do
    expect(described_class::Glib.const_defined?(:MICRO_VERSION)).to be true
  end
end
