<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.10" tiledversion="1.11.2" name="gnarpius" tilewidth="16" tileheight="16" tilecount="1024" columns="32">
 <properties>
  <property name="cog2d._firstgid" type="int" value="1"/>
 </properties>
 <image source="../../images/gnarpius.png" width="512" height="512"/>
 <tile id="36" probability="0.1"/>
 <tile id="68" probability="0.2"/>
 <tile id="100" probability="0.05"/>
 <wangsets>
  <wangset name="terrain" type="mixed" tile="-1">
   <wangcolor name="main" color="#ff0000" tile="-1" probability="0.05"/>
   <wangtile tileid="33" wangid="0,0,1,1,1,0,0,0"/>
   <wangtile tileid="34" wangid="0,0,1,1,1,1,1,0"/>
   <wangtile tileid="35" wangid="0,0,0,0,1,1,1,0"/>
   <wangtile tileid="36" wangid="1,1,1,1,1,1,1,1"/>
   <wangtile tileid="65" wangid="1,1,1,1,1,0,0,0"/>
   <wangtile tileid="66" wangid="1,1,1,1,1,1,1,1"/>
   <wangtile tileid="67" wangid="1,0,0,0,1,1,1,1"/>
   <wangtile tileid="68" wangid="1,1,1,1,1,1,1,1"/>
   <wangtile tileid="97" wangid="1,1,1,0,0,0,0,0"/>
   <wangtile tileid="98" wangid="1,1,1,0,0,0,1,1"/>
   <wangtile tileid="99" wangid="1,0,0,0,0,0,1,1"/>
   <wangtile tileid="100" wangid="1,1,1,1,1,1,1,1"/>
  </wangset>
 </wangsets>
</tileset>
