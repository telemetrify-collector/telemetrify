<?xml version="1.0"?>
<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
xmlns:tfc="http://tail-f.com/ns/config/1.0"
xmlns:al="http://tail-f.com/ns/ncs-alarms">
  <xsl:output omit-xml-declaration="yes" method="xml" indent="yes"/>
  <xsl:strip-space elements="*"/>
  <!-- Remove all attributes and leave only the data element-->
  <xsl:template match="node()">
    <xsl:copy>
      <xsl:apply-templates select="node()" />
    </xsl:copy>
  </xsl:template>
  <!-- Remove top level config node -->
  <xsl:template match="/tfc:config">
    <xsl:apply-templates select="node()" />
  </xsl:template>
  <!-- Strip timestamps -->
  <xsl:template match="al:last-status-change/node() | al:event-time/node()">
    <xsl:value-of select="'Stripped for compare'"/>
  </xsl:template>
</xsl:stylesheet>
