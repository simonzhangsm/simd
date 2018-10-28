<?xml version="1.0" encoding="UTF-8"?>
<!--

    This file is part of cppreference-doc

/**********************************************************************
 * BIGMATH INSIGHT CONFIDENTIAL
 *
 * Copyright (C) 2016-2018 BIGMATH CORPORATION, All Rights Reserved.
 *
 * @Author: Simon Zhang on 19 Oct 2018
 * @EMail: simon.zhangsm@hotmail.com
 * @Version: $SIMD_LIB_VERSION
 *
 * These source codes are subject to the terms and conditions defined
 * in 'LICENSE', which is part of this source code package. Write to
 * LICENSE@BIGMATH.COM for more authorization requirements, or obtain
 * an entire copy of license agreement at http://bigmath.com/license.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * **********************************************************************/
-->
<xsl:stylesheet
  version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:str="http://exslt.org/strings">

  <xsl:output
    doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN"
    doctype-system="http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd"
    omit-xml-declaration="yes"
  />

  <xsl:template match="node()|@*">
    <xsl:copy>
      <xsl:apply-templates select="node()|@*"/>
    </xsl:copy>
  </xsl:template>

  <!-- remove useless UI elements-->
  <xsl:template match="//*[contains(@class, 'noprint ')]"/>
  <xsl:template match="//*[contains(@class, ' noprint')]"/>
  <xsl:template match="//*[@class='editsection']"/>
  <xsl:template match="//*[@class='noprint']"/>
  <xsl:template match="//*[@class='printfooter']"/>
  <xsl:template match="//*[@class='catlinks']"/>

  <!-- remove comments -->
  <xsl:template match="comment()"/>

  <!-- remove external links to unused resources -->
  <xsl:template match="/html/head/link[@rel = 'alternate']"/>
  <xsl:template match="/html/head/link[@rel = 'search']"/>
  <xsl:template match="/html/head/link[@rel = 'edit']"/>
  <xsl:template match="/html/head/link[@rel = 'EditURI']"/>
  <xsl:template match="/html/head/link[@rel = 'shortcut icon']"/>

  <!-- remove Google Analytics scripts -->
  <xsl:template match="/html/body/script[contains(text(),'google-analytics.com/ga.js')]"/>
  <xsl:template match="/html/body/script[contains(@src, 'google-analytics.com/ga.js')]"/>
  <xsl:template match="/html/body/script[contains(text(),'pageTracker')]"/>

  <!-- remove unused stats -->
  <xsl:template match="/html/body/script[contains(text(),'wgBackendResponseTime')]"/>

</xsl:stylesheet>
