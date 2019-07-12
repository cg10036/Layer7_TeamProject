<?php
if($_GET['Mode'] == "Check")
{
	if($_GET['Word'] == "")
	{
		die("KO");
	}
	$content = file_get_contents("http://suggest.dic.daum.net/dic_all_ctsuggest?mod=json&code=utf_in_out&enc=utf&cate=lan&q=".$_GET['Word']);
	if(strpos($content, "|".$_GET['Word']."|") !== false)
	{
		die("OK");
	}
	else
	{
		die("KO");
	}
}
else if($_GET['Mode'] == "Find")
{
	if($_GET['Word'] == "")
	{
		die("KO");
	}
	$content = file_get_contents("http://wordfind.co.kr/start-word/".$_GET['Word']."_3.html");
	strip_tags($content);
	$content = preg_replace("(\<(/?[^\>]+)\>)", "", $content);
	$content = preg_replace("/[^A-Za-z|\x20]/", "", $content);
	$content = preg_replace("/\s{2,}/", " ", $content);
	$content = substr($content, 107);
	$content = substr($content, 0, strpos($content, " nbsp "));
	$content = explode(" ", $content);
	for($i = 0;$i < count($content);$i++)
	{
		if(substr($content[$i], 0, 1) === $_GET['Word'] && strtolower($content[$i]) === $content[$i] && strlen($content[$i]) > 1)
		{
			echo $content[$i]."<br>";
		}
	}
}
else
{
	die("Unknown Mode");
}
?>
