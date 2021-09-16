<!DOCTYPE html>
<html lang='zh-CN'>
<head>
<title>docs/zh/docs/Virtualization/LibcarePlus.md · openEuler/docs - Gitee.com</title>
<meta content='on' http-equiv='x-dns-prefetch-control'>
<link href='//e.gitee.com' rel='dns-prefetch'>
<link href='//files.gitee.com' rel='dns-prefetch'>
<link href='//toscode.gitee.com' rel='dns-prefetch'>
<link href='https://assets.gitee.com' rel='dns-prefetch'>
<link href='https://portrait.gitee.com' rel='dns-prefetch'>
<link rel="shortcut icon" type="image/vnd.microsoft.icon" href="https://assets.gitee.com/assets/favicon-9007bd527d8a7851c8330e783151df58.ico" />
<link rel="canonical" href="https://gitee.com/openeuler/docs" />
<meta content='gitee.com/openeuler/docs git https://gitee.com/openeuler/docs.git' name='go-import'>
<meta charset='utf-8'>
<meta content='always' name='referrer'>
<meta content='Gitee' property='og:site_name'>
<meta content='Object' property='og:type'>
<meta content='http://gitee.com/openeuler/docs/blob/stable2-20.03_LTS_SP1/docs/zh/docs/Virtualization/LibcarePlus.md' property='og:url'>
<meta content='https://gitee.com/static/images/logo_themecolor.png' itemprop='image' property='og:image'>
<meta content='docs/zh/docs/Virtualization/LibcarePlus.md · openEuler/docs - Gitee.com' itemprop='name' property='og:title'>
<meta content='This is openEuler documentation repository,' property='og:description'>
<meta content='码云,Gitee,代码托管,Git,Git@OSC,Gitee.com,开源,内源,项目管理,版本控制,开源代码,代码分享,项目协作,开源项目托管,免费代码托管,Git代码托管,Git托管服务' name='Keywords'>
<meta content='This is openEuler documentation repository,' itemprop='description' name='Description'>

<meta content="IE=edge" http-equiv="X-UA-Compatible" />
<meta name="csrf-param" content="authenticity_token" />
<meta name="csrf-token" content="Z6NkNGFVGG5dTeVxbDLRO5mQ38Y+ASqgWQ60tz5Lxwpv1zzRjawHcgH7I1lWTu8dr4/I2CUXkUoYERC52zSDVw==" />

<link rel="stylesheet" media="all" href="https://assets.gitee.com/assets/application-a8ad1adc644ceb7826706efe3ad137ed.css" />
<script>
//<![CDATA[
window.gon = {};gon.locale="zh-CN";gon.sentry_dsn=null;gon.baidu_register_hm_push=null;gon.sensor={"server_url":"https://haveaniceday.gitee.com:3443/sa?project=production","page_type":"其他"};gon.info={"controller_path":"blob","action_name":"show","current_user":false};gon.tour_env={"current_user":null,"action_name":"show","original_url":"http://gitee.com/openeuler/docs/blob/stable2-20.03_LTS_SP1/docs/zh/docs/Virtualization/LibcarePlus.md","controller_path":"blob"};gon.http_clone="https://gitee.com/openeuler/docs.git";gon.user_project="openeuler/docs";gon.manage_branch="管理分支";gon.manage_tag="管理标签";gon.enterprise_id=5292411;gon.create_reaction_path="/openeuler/docs/reactions";gon.ref="stable2-20.03_LTS_SP1";
//]]>
</script>
<script src="https://assets.gitee.com/assets/static/sensor-5984a2e9c24e9047ba28a1ddc8442b67.js"></script>
<script src="https://assets.gitee.com/assets/static/sentry-5.1.0-a823fb0be1b61c5d7ca4a89f0536cb0a.js"></script>
<script src="https://assets.gitee.com/assets/application-d8037a605419bdeda04f4b18452be15e.js"></script>
<script src="https://assets.gitee.com/assets/lib/jquery.timeago.zh-CN-4a4818e98c1978d2419ab19fabcba740.js"></script>

<link rel="stylesheet" media="all" href="https://assets.gitee.com/assets/projects/application-705b8d764a3d4201795216aad0ed4b70.css" />
<script src="https://assets.gitee.com/assets/projects/app-e70b2c80a4066f6b27c7c63671aac1fd.js"></script>

<script src="//res.wx.qq.com/open/js/jweixin-1.2.0.js"></script>
<script>
  var title = document.title.replace(/( - Gitee| - 码云)$/, '')
      imgUrl = '';
  
  document.addEventListener('DOMContentLoaded', function(event) {
    var imgUrlEl = document.querySelector('.readme-box .markdown-body > img, .readme-box .markdown-body :not(a) > img');
    imgUrl = imgUrlEl && imgUrlEl.getAttribute('src');
  
    if (!imgUrl) {
      imgUrlEl = document.querySelector('meta[itemprop=image]');
      imgUrl = imgUrlEl && imgUrlEl.getAttribute('content');
      imgUrl = imgUrl || "https://gitee.com/static/images/logo_themecolor.png";
    }
  
    wx.config({
      debug: false,
      appId: "wxff219d611a159737",
      timestamp: "1631795384",
      nonceStr: "6ea6c5f9d349f1386df2390a74377154",
      signature: "c8096e439fbcdc330a6204238572e60dd98efe91",
      jsApiList: [
        'onMenuShareTimeline',
        'onMenuShareAppMessage'
      ]
    });
  
    wx.ready(function () {
      wx.onMenuShareTimeline({
        title: title, // 分享标题
        link: "https://gitee.com/openeuler/docs/blob/stable2-20.03_LTS_SP1/docs/zh/docs/Virtualization/LibcarePlus.md", // 分享链接，该链接域名或路径必须与当前页面对应的公众号JS安全域名一致
        imgUrl: imgUrl // 分享图标
      });
      wx.onMenuShareAppMessage({
        title: title, // 分享标题
        link: "https://gitee.com/openeuler/docs/blob/stable2-20.03_LTS_SP1/docs/zh/docs/Virtualization/LibcarePlus.md", // 分享链接，该链接域名或路径必须与当前页面对应的公众号JS安全域名一致
        desc: document.querySelector('meta[name=Description]').getAttribute('content'),
        imgUrl: imgUrl // 分享图标
      });
    });
    wx.error(function(res){
      console.error('err', res)
    });
  })
</script>

<script type='text/x-mathjax-config'>
MathJax.Hub.Config({
  tex2jax: {
    inlineMath: [['$','$'], ['\\(','\\)']],
    displayMath: [["$$","$$"],["\\[","\\]"]],
    processEscapes: true,
    skipTags: ['script', 'noscript', 'style', 'textarea', 'pre', 'code'],
    ignoreClass: "container|files",
    processClass: "markdown-body"
  }
});
</script>
<script src="https://assets.gitee.com/uploads/resources/MathJax-2.7.2/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script>

<script>
  (function () {
    var messages = {
      'zh-CN': {
        addResult: '增加 <b>{term}</b>',
        count: '已选择 {count}',
        maxSelections: '最多 {maxCount} 个选择',
        noResults: '未找到结果',
        serverError: '连接服务器时发生错误'
      },
      'zh-TW': {
        addResult: '增加 <b>{term}</b>',
        count: '已選擇 {count}',
        maxSelections: '最多 {maxCount} 個選擇',
        noResults: '未找到結果',
        serverError: '連接服務器時發生錯誤'
      }
    }
  
    if (messages[gon.locale]) {
      $.fn.dropdown.settings.message = messages[gon.locale]
    }
  }());
</script>

<script>
  var userAgent = navigator.userAgent;
  var isLessIE11 = userAgent.indexOf('compatible') > -1 && userAgent.indexOf('MSIE') > -1;
  if(isLessIE11){
    var can_access = ""
    if (can_access != "true"){
      window.location.href = "/incompatible.html";
    }
  }
  document.addEventListener("error", function (ev) {
    var elem = ev.target;
    if (elem.tagName.toLowerCase() === 'img') {
      elem.src = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMgAAADICAAAAACIM/FCAAACh0lEQVR4Ae3ch5W0OgyG4dt/mQJ2xgQPzJoM1m3AbALrxzrf28FzsoP0HykJEEAAAUQTBBBAAAEEEEAAAQQQQAABBBBAAAEEEEAAAQQQQAABBBBAAAEEkKK0789+GK/I2ezfQB522PnS1qc8pGgXvr4tE4aY0XOUWlGImThWgyCk6DleixzE7qwBkg/MGiDPlVVAyp1VQGrPKiACDhFI6VkF5LmzCki+sg7IwDoglnVAil0IMkeG9CyUiwsxLFUVFzJJOQaKCjFCDN9RXMjIX7W6ztZXZDKKCyn8sWJvH+nca7WHDN9lROlAliPH9iRKCPI4cswFJQWxB46toLQgQ9jhn5QYZA9DOkoMUoQde5YapAxDWkoNYsOQR3KQd9CxUnIQF4S49CB9ENKlBxmDEKsFUgMCCCCAAHIrSF61f6153Ajy8nyiPr8L5MXnmm4CyT2fzN4DUvHZ+ntA2tOQBRBAAAEEEEAAAQQQ7ZBaC6TwSiDUaYHQ2yuB0MN+ft+43whyrs4rgVCjBUKTFshLC6TUAjGA3AxSaYFYLZBOC2RUAsk8h5qTg9QcbEoOsoQhQ2qQhsO5xCD5dgB5JQaZ+KBKGtKecvR81Ic0ZDjByKdDx0rSEDZ/djQbH+bkIdvfJFm98BfV8hD2zprfVdlu9PxVeyYAkciREohRAplJCaRSAplJCcQogTjSAdlyHRBvSAekJR0QRzogA+mADJkOiCPSAPEtqYBshlRAXC43hxix2QiOuEZkVERykGyNo9idIZKE0HO7XrG6OiMShlDWjstVzdPgXtUH9v0CEidAAAEEEEAAAQQQQAABBBBAAAEEEEAAAQQQQAABBBBAAAEEEEAAAQQQQP4HgjZxTpdEii0AAAAASUVORK5CYII=";
    }
  }, true);
</script>
</head>

<body class='git-project lang-zh-CN large'>
<header class='common-header fixed noborder' id='git-header-nav'>
<div class='ui container'>
<div class='ui menu header-menu header-container'>
<div class='git-nav-expand-bar'>
<i class='iconfont icon-mode-table'></i>
</div>
<div class='gitee-nav__sidebar'>
<div class='gitee-nav__sidebar-container'>
<div class='gitee-nav__sidebar-top'>
<div class='gitee-nav__avatar-box'></div>
<div class='gitee-nav__buttons-box'>
<a class="ui button small fluid orange" href="/login">登录</a>
<a class="ui button small fluid basic is-register" href="/signup">注册</a>
</div>
</div>
<div class='gitee-nav__sidebar-middle'>
<div class='gitee-nav__sidebar-list'>
<ul>
<li class='gitee-nav__sidebar-item'>
<a href="/explore"><i class='iconfont icon-ic-discover'></i>
<span class='gitee-nav__sidebar-name'>开源软件</span>
</a></li>
<li class='gitee-nav__sidebar-item'>
<a href="/enterprises"><i class='iconfont icon-ic-enterprise'></i>
<span class='gitee-nav__sidebar-name'>企业版</span>
</a></li>
<li class='gitee-nav__sidebar-item'>
<a href="/education"><i class='iconfont icon-ic-education'></i>
<span class='gitee-nav__sidebar-name'>高校版</span>
</a></li>
<li class='gitee-nav__sidebar-item split-line'></li>
<li class='gitee-nav__sidebar-item'>
<a href="/search"><i class='iconfont icon-ic-search'></i>
<span class='gitee-nav__sidebar-name'>搜索</span>
</a></li>
<li class='gitee-nav__sidebar-item'>
<a href="/help"><i class='iconfont icon-help-circle'></i>
<span class='gitee-nav__sidebar-name'>帮助中心</span>
</a></li>
<li class='gitee-nav__sidebar-item'>
<a href="/terms"><i class='iconfont icon-file'></i>
<span class='gitee-nav__sidebar-name'>使用条款</span>
</a></li>
<li class='gitee-nav__sidebar-item'>
<a href="/about_us"><i class='iconfont icon-issuepx'></i>
<span class='gitee-nav__sidebar-name'>关于我们</span>
</a></li>
</ul>
</div>
</div>
<div class='gitee-nav__sidebar-bottom'>
<div class='gitee-nav__sidebar-close-button'>
<i class='fa fa-angle-double-left'></i>
</div>
</div>
</div>
</div>

<div class='item gitosc-logo'>
<a href="/"><img alt='Gitee — 基于 Git 的代码托管和研发协作平台' class='ui inline image' height='28' src='/static/images/logo.svg?t=158106664' title='Gitee — 基于 Git 的代码托管和研发协作平台' width='95'>
<img alt='Gitee — 基于 Git 的代码托管和研发协作平台' class='ui inline black image' height='28' src='/static/images/logo-black.svg?t=158106664' title='Gitee — 基于 Git 的代码托管和研发协作平台' width='95'>
</a></div>
<a title="开源软件" class="item " href="/explore">开源软件
</a><a title="企业版" class="item " href="/enterprises">企业版
<sup class='ui red label'>
特惠
</sup>
</a><a title="高校版" class="item " href="/education">高校版
</a><a title="私有云" class="item" target="_blank" href="https://gitee.cn?utm_source=giteecom">私有云
</a><a title="博客" class="item" id="gitee-blog" target="_blank" href="https://blog.gitee.com/">博客
</a><div class='center responsive-logo'>
<a href="/"><img alt='Gitee — 基于 Git 的代码托管和研发协作平台' class='ui inline image' height='24' src='/static/images/logo.svg?t=158106664' title='Gitee — 基于 Git 的代码托管和研发协作平台' width='85'>
<img alt='Gitee — 基于 Git 的代码托管和研发协作平台' class='ui inline black image' height='24' src='/static/images/logo-black.svg?t=158106664' title='Gitee — 基于 Git 的代码托管和研发协作平台' width='85'>
</a></div>
<div class='right menu userbar right-header' id='git-nav-user-bar'>
<form class="ui item" id="navbar-search-form" data-text-require="搜索关键字不能少于1个" data-text-filter="搜索格式不正确" action="/search" accept-charset="UTF-8" method="get"><input name="utf8" type="hidden" value="&#x2713;" />
<input type="hidden" name="type" id="navbar-search-type" />
<input type="hidden" name="fork_filter" id="fork_filter" value="on" />
<div class='ui search header-search'>
<input type="text" name="q" id="navbar-search-input" value="" class="prompt" placeholder="搜开源" />
</div>
</form>

<script>
  var can_search_in_repo = 1,
      repo = "VG1wWmVrNUVXVFJPYlVVelRtcE9iV0UzTmpObWE3NjNm",
      reponame = "openeuler/docs";
  
  $(function() {
    var $search = $('#navbar-search-form .ui.search');
    $search.search({
      apiSettings: {
        url: '/search/relative_project?q={query}',
        onResponse: function (res) {
          if (res && res.status === 200 && res.data) {
            var query = htmlSafe($search.search('get value'));
  
            res.data.map(function (item) {
              item.path_ns = '/' + item.path_ns;
              item.icon = 'iconfont icon-project-public';
            });
            res.data.unshift({
              name_ns: "在全站搜索 <b class='hl'>" + query +"</b> 相关项目",
              path_ns: '/search?fork_filter=on&q=' + query,
              icon: 'iconfont icon-search'
            });
            return res;
          } else {
            return { data: [] };
          }
        }
      },
      fields: {
        results: 'data',
        description: 'name_ns',
        url: 'path_ns',
        icon: 'icon'
      },
      minCharacters: 1,
      maxResults: 10,
      searchDelay: 250,
      showNoResults: false,
      transition: 'fade'
    });
  });
</script>

<div class='ui item' id='feature-update-notice'>
<div class='notice-update-icon'>
<a class="notice-update-popup click-knowed" title="" href="javascript:void(0)"><img alt="功能更新" title="" class="bubl_icon bubl-off-icon" src="https://assets.gitee.com/assets/bulb_off-24ee940be20998aace89a3f040cbc704.svg" />
<img alt="功能更新" title="" class="bubl_icon bubl-on-icon" src="https://assets.gitee.com/assets/bulb_on-3986b1dc417285398e3d15671bd8f261.svg" />
</a></div>
<div class='feature-update-notice-panel menu'>
<div class='notice-img'>
<img alt="" title="" class="notice-img-show" src="" />
</div>
<div class='notice-update-title'></div>
<div class='notice-update-des'></div>
<div class='notice-btn-list d-flex-between'>
<button name="button" type="button" class="ui basic orange button btn-notice btn-knowed click-knowed" style="margin-right: 0">我知道了</button>
<a class="ui button orange btn-notice btn-details click-knowed" target="_blank" href="">查看详情</a>
</div>
</div>
</div>

<a class="item git-nav-user__login-item" sa_evt="login_show" sa_referrer_url="" sa_referrer_action="站导航右上角-登录按钮" sa_referrer_type="其他" href="/login">登录
</a><a class="item git-nav-user__register-item" sa_evt="register_show" sa_referrer_url="" sa_referrer_action="站导航右上角-注册按钮" sa_referrer_type="其他" href="/signup">注册
</a><script>
  $('.destroy-user-session').on('click', function() {
    $.cookie('access_token', null, { path: '/' });
  })
</script>

</div>
</div>
</div>
</header>
<script>
  Gitee.initNavbar()
  Gitee.initRepoRemoteWay()
  $.cookie('user_locale',null)
</script>

<script>
  var userAgent = navigator.userAgent;
  var isLessIE11 = userAgent.indexOf('compatible') > -1 && userAgent.indexOf('MSIE') > -1;
  if(isLessIE11){
    var can_access = ""
    if (can_access != "true"){
      window.location.href = "/incompatible.html";
    }
  }
</script>

<div class='fixed-notice-infos'>
<div class='all-messages'>
<div class='ui info message' id='git-bulletin'>
<a href=https://my.oschina.net/gitosc/blog/5262211 target='_blank'>新一期 Gitee Talk 来啦！一起和产品经理聊聊Gitee企业版新特性>>></a>
<i class='icon remove' id='remove-bulletin'></i>
</div>
</div>
<div class='ui container'>
<div class='flash-messages' id='messages-container'></div>
</div>
<script>
  (function() {
    $(function() {
      var $error_box, alertTip, notify_content, notify_options, template;
      template = '<div data-notify="container" class="ui {0} message" role="alert">' + '<i data-notify="dismiss" class="close icon"></i>' + '<span data-notify="message">{2}</span>' + '</div>';
      notify_content = null;
      notify_options = {};
      alertTip = '';
      $error_box = $(".flash_error.flash_error_box");
      if (notify_options.type === 'error' && $error_box.length > 0 && !$.isEmptyObject(notify_content.message)) {
        if (notify_content.message === 'captcha_fail') {
          alertTip = "验证码不正确";
        } else if (notify_content.message === 'captcha_expired') {
          alertTip = "验证码已过期，请点击刷新";
        } else if (notify_content.message === 'not_found_in_database') {
          alertTip = "帐号或者密码错误";
        } else if (notify_content.message === 'not_found_and_show_captcha') {
          alertTip = "帐号或者密码错误";
        } else if (notify_content.message === 'phone_captcha_fail') {
          alertTip = "手机验证码不通过";
        } else {
          alertTip = notify_content.message;
        }
        return $error_box.html(alertTip).show();
      } else if (notify_content) {
        if ("show" === 'third_party_binding') {
          return $('#third_party_binding-message').html(notify_content.message).addClass('ui message red');
        }
        notify_options.delay = 3000;
        notify_options.template = template;
        notify_options.offset = {
          x: 10,
          y: 30
        };
        notify_options.element = '#messages-container';
        return $.notify(notify_content, notify_options);
      }
    });
  
  }).call(this);
</script>

</div>
<script>
  (function() {
    $(function() {
      var setCookie;
      setCookie = function(name, value) {
        $.cookie(name, value, {
          path: '/',
          expires: 365
        });
      };
      $('#remove-bulletin, #remove-bulletin-dashboard').on('click', function() {
        setCookie('remove_bulletin', "gitee-maintain-1631683700");
        $('#git-bulletin').hide();
      });
      $('#remove-member-bulletin').on('click', function() {
        setCookie('remove_member_bulletin', "gitee_member_bulletin");
        $(this).parent().hide();
      });
      return $('#remove-gift-bulletin').on('click', function() {
        setCookie('remove_gift_bulletin', "gitee-gift-bulletin");
        $(this).parent().hide();
      });
    });
  
  }).call(this);
</script>
<script>
  function closeMessageBanner(pthis, type, val) {
    var json = {}
  
    val = typeof val === 'undefined' ? null : val
    $(pthis).parent().remove()
    if (type === 'out_of_enterprise_member') {
      json = {type: type, data: val}
    } else if (type === 'enterprise_overdue') {
      json = {type: type, data: val}
    }
    $.post('/profile/close_flash_tip', json)
  }
</script>

<div class='site-content'>
<div class='git-project-header'>
<div class='fixed-notice-infos'>
<div class='ui info icon floating message green' id='fetch-ok' style='display: none'>
<div class='content'>
<div class='header status-title'>
<i class='info icon status-icon'></i>
代码拉取完成，页面将自动刷新
</div>
</div>
</div>
<div class='ui info icon floating message error' id='fetch-error' style='display: none'>
<div class='content'>
<div class='header status-title'>
<i class='info icon status-icon'></i>
<span class='error_msg'></span>
</div>
</div>
</div>
</div>
<div class='ui container'>
<div class='git-project-categories'>
<a href="/explore">开源项目</a>
<span class='symbol'>></span>
<a href="/explore/other-open-source">其他开源</a>
<span class='symbol'>&gt;</span>
<a href="/explore/os">操作系统</a>
<span class='symbol and-symbol'>&&</span>
</div>

<div class='git-project-header-details'>
<div class='git-project-header-container'>
<div class='git-project-header-actions'>
<div class='ui tiny modal project-donate-modal' id='project-donate-modal'>
<i class='iconfont icon-close close'></i>
<div class='header'>捐赠</div>
<div class='content'>
捐赠前请先登录
</div>
<div class='actions'>
<a class='ui blank button cancel'>取消</a>
<a class='ui orange ok button' href='/login'>前往登录</a>
</div>
</div>
<div class='ui small modal wepay-qrcode'>
<i class='iconfont icon-close close'></i>
<div class='header'>
扫描微信二维码支付
<span class='wepay-cash'></span>
</div>
<div class='content weqcode-center'>
<img id='wepay-qrcode' src=''>
</div>
<div class='actions'>
<div class='ui cancel blank button'>取消</div>
<div class='ui ok orange button'>
支付完成
</div>
</div>
</div>
<div class='ui mini modal' id='confirm-alipay-modal'>
<div class='header'>支付提示</div>
<div class='content'>
将跳转至支付宝完成支付
</div>
<div class='actions'>
<div class='ui approve orange button'>
确定
</div>
<div class='ui blank cancel button'>
取消
</div>
</div>
</div>

<span class='ui buttons basic watch-container'>
<div class='ui dropdown button js-project-watch' data-watch-type='unwatch'>
<input type='hidden' value=''>
<i class='iconfont icon-watch'></i>
<div class='text'>
Watch
</div>
<i class='dropdown icon'></i>
<div class='menu'>
<a data-value="unwatch" class="item" sa_evt="loginInform_show" sa_referrer_url="" sa_referrer_action="Watch" sa_referrer_type="其他" rel="nofollow" data-method="post" href="/openeuler/docs/unwatch"><i class='iconfont icon-msg-read'></i>
不关注
</a><a data-value="watching" class="item" sa_evt="loginInform_show" sa_referrer_url="" sa_referrer_action="Watch" sa_referrer_type="其他" rel="nofollow" data-method="post" href="/openeuler/docs/watch"><i class='iconfont icon-msg-read'></i>
关注所有动态
</a><a data-value="releases_only" class="disabled item" sa_evt="loginInform_show" sa_referrer_url="" sa_referrer_action="Watch" sa_referrer_type="其他" rel="nofollow" data-method="post" href="/openeuler/docs/release_only_watch"><i class='iconfont icon-msg-read'></i>
仅关注版本发行动态
</a><a data-value="ignoring" class="item" sa_evt="loginInform_show" sa_referrer_url="" sa_referrer_action="Watch" sa_referrer_type="其他" rel="nofollow" data-method="post" href="/openeuler/docs/ignoring_watch"><i class='iconfont icon-msg-read'></i>
关注但不提醒动态
</a></div>
</div>
<style>
  .js-project-watch .text .iconfont {
    display: none; }
  .js-project-watch a, .js-project-watch a:hover {
    color: #000; }
  .js-project-watch .item > .iconfont {
    visibility: hidden;
    margin-left: -10px; }
  .js-project-watch .selected .iconfont {
    visibility: visible; }
  .js-project-watch .menu {
    margin-top: 4px !important; }
</style>
<script>
  $('.js-project-watch').dropdown({
    action: 'select',
    onChange: function(value, text, $selectedItem) {
      var type = value === 'unwatch' ? 'Watch' : 'Watching';
      $(this).children('.text').text(type);
      $(this).dropdown('set selected', value)
    }
  });
</script>

<a class="ui button action-social-count" title="59" href="/openeuler/docs/watchers">59
</a></span>
<span class='basic buttons star-container ui'>
<a class="ui button star" sa_evt="loginInform_show" sa_referrer_url="" sa_referrer_action="Star" sa_referrer_type="其他" href="/login"><i class='iconfont icon-star'></i>
Star
</a><a class="ui button action-social-count " title="73" href="/openeuler/docs/stargazers">73
</a></span>
<span class='ui basic buttons fork-container' title='无权 Fork 此仓库'>
<a class="ui button fork" title="你必须登录后才可以fork一个仓库" sa_evt="loginInform_show" sa_referrer_url="" sa_referrer_action="Fork" sa_referrer_type="其他" href="/login"><i class='iconfont icon-fork'></i>
Fork
</a><a class="ui button action-social-count disabled-style" title="144" href="/openeuler/docs/members">144
</a></span>
</div>
<h2 class='git-project-title mt-0 mb-0'>
<span class="project-title"><a href='/open_euler'><i class="iconfont icon-enterprise-badge" title="这是一个企业仓库"></i></a> <i class="project-icon iconfont icon-project-public" title="这是一个公开仓库"></i> <a title="openEuler" class="author" href="/openeuler">openEuler</a> / <a title="docs" class="repository" target="" style="padding-bottom: 0px; margin-right: 4px" sa_evt="repoClick" sa_location="其他" sa_url="" sa_repo_id="6634686" href="/openeuler/docs">docs</a></span><span class="project-badges"><style>
  .gitee-modal {
    width: 500px !important; }
</style>
</span>
<input type="hidden" name="project_title" id="project_title" value="openEuler/docs" />
</h2>
</div>
</div>
</div>
<script>
  var title_import_url = "false";
  var title_post_url = "/openeuler/docs/update_import";
  var title_fork_url = "/openeuler/docs/sync_fork";
  var title_project_path = "docs";
  var title_p_name = "docs";
  var title_p_id= "6634686";
  var title_description = "This is openEuler documentation repository,";
  var title_form_authenticity_token = "XKHvpRG5EsNhIBWs6nJBNg0XNYPK1y/y/UJVJUk0PIBU1bdA/UAN3z2W04TQDn8QOwgindHBlBi8XfErrEt43Q==";
  var watch_type = "unwatch";
  
  $('.js-project-watch').dropdown('set selected', watch_type);
  $('.checkbox.sync-wiki').checkbox();
</script>
<style>
  i.loading {
    -webkit-animation: icon-loading 1.2s linear infinite;
    animation: icon-loading 1.2s linear infinite;
  }
  .qrcode_cs {
    float: left;
  }
  .check-sync-wiki {
    float: left;
    height: 28px;
    line-height: 28px;
  }
  .sync-wiki-warn {
    color: #e28560;
  }
</style>

<div class='git-project-nav'>
<div class='ui container'>
<div class='ui secondary pointing menu'>
<a class="item active" href="/openeuler/docs/tree/stable2-20.03_LTS_SP1"><i class='iconfont icon-code'></i>
代码
</a><a class="item " href="/openeuler/docs/issues"><i class='iconfont icon-task'></i>
Issues
<span class='ui mini circular label'>
83
</span>
</a><a class="item big-wide " href="/openeuler/docs/pulls"><i class='iconfont icon-pull-request'></i>
Pull Requests
<span class='ui mini circular label'>
12
</span>
</a><a class="item " href="/openeuler/docs/wikis"><i class='iconfont icon-wiki'></i>
Wiki
</a><a class="item  " href="/openeuler/docs/graph/master"><i class='iconfont icon-statistics'></i>
统计
</a><div class='item project-devops-item'>
<div class='ui pointing top right dropdown project-devops-dropdown'>
<div class='text'>
<i class='iconfont icon-devops'></i>
DevOps
</div>
<i class='dropdown icon'></i>
<div class='menu' style='display:none'>
<a class="item" href="/openeuler/docs/gitee_go"><img src="https://assets.gitee.com/assets/giteego-7ec42270742374f05850d0d3ad09e303.png" alt="Giteego" />
<div class='item-title'>
Gitee Go
</div>
</a><a class="item" target="_blank" href="https://gitee.com/help/articles/4285"><img src="https://assets.gitee.com/assets/baidu_efficiency_cloud-81a98c2eb67fac83b1453ca3d2feb326.svg" alt="Baidu efficiency cloud" />
<div class='item-title'>
百度效率云
</div>
</a><a class="item" target="_blank" href="https://gitee.com/help/articles/4318"><img src="https://assets.gitee.com/assets/cloudbase-1197b95ea3398aff1df7fe17c65a6d42.png?20200925" alt="Cloudbase" />
<div class='item-title'>
腾讯云托管
</div>
</a><a class="item" target="_blank" href="https://gitee.com/help/articles/4330"><img src="https://assets.gitee.com/assets/cloud_serverless-686cf926ced5d6d2f1d6e606d270b81e.png" alt="Cloud serverless" />
<div class='item-title'>
腾讯云 Serverless
</div>
</a><a class="item" target="_blank" href="https://gitee.com/help/articles/4193"><img src="https://assets.gitee.com/assets/jenkins_for_gitee-554ec65c490d0f1f18de632c48acc4e7.png" alt="Jenkins for gitee" />
<div class='item-title'>
Jenkins for Gitee
</div>
</a></div>
</div>
</div>
<div class='item'>
<div class='ui pointing top right dropdown git-project-service'>
<div class='text'>
<i class='iconfont icon-service'></i>
服务
</div>
<i class='dropdown icon'></i>
<div class='menu' style='display:none'>
<a class="item" href="/openeuler/docs/pages"><img src="/static/images/logo-en.svg" alt="Logo en" />
<div class='item-title'>
Gitee Pages
</div>
</a><a class="item" href="/openeuler/docs/javadoc"><img src="https://assets.gitee.com/assets/maven-bd58aee84f266d64d4b8ce5b006a9fcf.png" alt="Maven" />
<div class='item-title'>
JavaDoc
</div>
</a><a class="item" href="/openeuler/docs/phpdoc"><img src="https://assets.gitee.com/assets/phpdoc-a99f87c2feaa2fd99e5065377a39487e.png" alt="Phpdoc" />
<div class='item-title'>
PHPDoc
</div>
</a><a class="item" href="/openeuler/docs/quality_analyses?platform=sonar_qube"><img src="https://assets.gitee.com/assets/sonar_mini-5e1b54bb9f6c951d97fb778ef623afea.png" alt="Sonar mini" />
<div class='item-title'>
质量分析
</div>
</a><a class="item" href="/openeuler/docs/quality_analyses?platform=codesafe"><img width="100%" src="https://assets.gitee.com/assets/codesafe_mini-accbe1e555e9864c552620240d10e4de.png" alt="Codesafe mini" />
<div class='item-title'>
奇安信代码卫士
</div>
</a><a class="item" href="/openeuler/docs/gitee_scans"><img src="https://assets.gitee.com/assets/giteescan-cd9ab4076bd751faf7e30888eb10f782.png" alt="Giteescan" />
<div class='item-title'>Gitee Scan</div>
</a><button class='ui orange basic button quit-button' id='quiting-button'>
我知道了，不再自动展开
</button>
</div>
</div>
</div>
</div>
</div>
</div>
<script>
  $('.git-project-nav .ui.dropdown').dropdown({ action: 'nothing' });
  var gitee_reward_config = JSON.parse(localStorage.getItem('gitee_reward_config') || null) || false
  var $settingText = $('.setting-text')
  // 如果没有访问过 
  if(!gitee_reward_config) $settingText.addClass('red-dot')
</script>
<style>
  .git-project-nav i.checkmark.icon {
    color: green;
  }
  #quiting-button {
    display: none;
  }
  
  .git-project-nav .dropdown .menu.hidden:after {
    visibility: hidden !important;
  }
</style>
<script>
  isSignIn = false
  isClickGuide = false
  $('#git-versions.dropdown').dropdown();
  $.ajax({
    url:"/openeuler/docs/access/add_access_log",
    type:"GET"
  });
  $('#quiting-button').on('click',function() {
    $('.git-project-service').click();
    if (isSignIn) {
      $.post("/projects/set_service_guide")
    }
    $.cookie("Serve_State", true, { expires: 3650, path: '/'})
    $('#quiting-button').hide();
  });
  if (!(isClickGuide || $.cookie("Serve_State") == 'true')) {
    $('.git-project-service').click()
    $('#quiting-button').show()
  }
</script>

</div>
<div class='ui container'>
<div class='register-guide'>
<div class='register-container'>
<div class='regist'>
加入 Gitee
</div>
<div class='description'>
与超过 600 万 开发者一起发现、参与优秀开源项目，私有仓库也完全免费 ：）
</div>
<a class="ui orange button free-registion" sa_evt="register_show" sa_referrer_url="" sa_referrer_action="免费加入" sa_referrer_type="其他" href="/signup?from=project-guide">免费加入</a>
<div class='login'>
已有帐号？
<a href="/login?from=project-guide">立即登录</a>
</div>
</div>
</div>

<div class='git-project-content-wrapper'>
<div class='ui grid' id='project-wrapper'>
<div class='sixteen wide column'>
<div class='git-project-content' id='git-project-content'>
<div class='row'>
<div class='git-project-desc-wrapper'>
<script>
  if (false) {
    gon.project_new_blob_path = "/openeuler/docs/new/stable2-20.03_LTS_SP1/docs/zh/docs/Virtualization/LibcarePlus.md"
    bindShowModal({
      el: $('.no-license .project-license__create'),
      complete: function(data, modal) {
        if (!data.haveNoChoice && !data.data) {
          Flash.show('请选择一项开源许可证')
        } else {
          location.href = gon.project_new_blob_path + '?license=' + data.data
        }
      },
      skip: function () {
        location.href = gon.project_new_blob_path + '?license'
      }
    });
  }
  
  $('i.help.circle.icon').popup({
    popup: '.no-license .ui.popup',
    position: 'right center'
  });
  
  $('#remove-no-license-message').on('click', function() {
    $.cookie("skip_repo_no_license_message_6634686", 'hide', { expires: 365 });
    $('#user-no-license-message').hide();
    return;
  });
</script>
</div>

</div>
<div class='git-project-bread' id='git-project-bread'>
<div class='ui horizontal list mr-1'>
<div class='item git-project-branch-item'>
<input type="hidden" name="path" id="path" value="docs/zh/docs/Virtualization/LibcarePlus.md" />
<div class='ui top left pointing dropdown gradient button dropdown-has-tabs' id='git-project-branch'>
<input type="hidden" name="ref" id="ref" value="stable2-20.03_LTS_SP1" />
<div class='default text'>
master
</div>
<i class='dropdown icon'></i>
<div class='menu'>
<div class='ui left icon search input'>
<i class='iconfont icon-search'></i>
<input class='search-branch' placeholder='搜索分支' type='text'>
</div>
<div class='tab-menu'>
<div class='tab-menu-action' data-tab='branches'>
<a class="ui link button" href="/openeuler/docs/branches">管理</a>
</div>
<div class='tab-menu-action' data-tab='tags'>
<a class="ui link button" href="/openeuler/docs/tags">管理</a>
</div>
<div class='tab-menu-item' data-placeholder='搜索分支' data-tab='branches'>
分支 (9)
</div>
<div class='tab-menu-item' data-placeholder='搜索标签' data-tab='tags'>
标签 (4)
</div>
</div>
<div class='tab scrolling menu' data-tab='branches'>
<div data-value="master" class="item"><span>master</span> <i class="iconfont icon-shieldlock protected-branch-popup" data-title="受保护分支" data-content="保护规则： master"></i></div>
<div data-value="stable2-21.03" class="item"><span>stable2-21.03</span></div>
<div data-value="stable2-20.03_LTS_SP2" class="item"><span>stable2-20.03_LTS_SP2</span></div>
<div data-value="stable2-20.03_LTS" class="item"><span>stable2-20.03_LTS</span></div>
<div data-value="stable2-20.03_LTS_SP1" class="item"><span>stable2-20.03_LTS_SP1</span></div>
<div data-value="stable2-20.09" class="item"><span>stable2-20.09</span></div>
<div data-value="20.03_LTS_Next" class="item"><span>20.03_LTS_Next</span></div>
<div data-value="website" class="item"><span>website</span></div>
<div data-value="1.0-base" class="item"><span>1.0-base</span></div>
</div>
<div class='tab scrolling menu' data-tab='tags'>
<div class='item' data-value='v1.0.3'>v1.0.3</div>
<div class='item' data-value='20.03-LTS'>20.03-LTS</div>
<div class='item' data-value='v1.0.2'>v1.0.2</div>
<div class='item' data-value='v1.0Base'>v1.0Base</div>
</div>
</div>
</div>
<style>
  .iconfont.icon-shieldlock {
    color: #8c92a4;
  }
</style>

<script>
  $(function () {
    Gitee.initTabsInDropdown($('#git-project-branch').dropdown({
      fullTextSearch: true,
      selectOnKeydown: true,
      action: function (text,value,el) {
        var oItemOrInitObject = el[0] || el
        var isNotSelect = oItemOrInitObject.dataset.tab && oItemOrInitObject.dataset.tab === 'branches'
        if(isNotSelect){
          console.warn("You didn't choose a branch")
          return
        } 
        var path = $('#path').val();
        var href = ['/openeuler/docs/tree', encodeURIComponent(value), path].join('/');
        window.location.href = href;
        return true
      },
      onNoResults: function (searchTerm) {
        //未找到结果
        return true
      },
    }));
    $('.protected-branch-popup').popup()
  })
</script>

</div>
</div>
<div class='git-project-right-actions pull-right'>
<div class='ui orange button' id='btn-dl-or-clone'>
克隆/下载
<i class='dropdown icon'></i>
</div>
<div class='git-project-download-panel for-project ui bottom right popup'>
<div class='ui small secondary pointing menu'>
<a class='item active' data-text='' data-type='http' data-url='https://gitee.com/openeuler/docs.git'>HTTPS</a>
<a class='item' data-text='' data-type='ssh' data-url='git@gitee.com:openeuler/docs.git'>SSH</a>
<a class='item' data-text="该仓库未启用SVN访问，请仓库管理员前往【&lt;a target='_blank' href=/openeuler/docs/settings&gt;仓库设置&lt;/a&gt;】开启。" data-type='svn' data-url=''>SVN</a>
<a class='item' data-text="该仓库未启用SVN访问，请仓库管理员前往【&lt;a target='_blank' href=/openeuler/docs/settings&gt;仓库设置&lt;/a&gt;】开启。" data-type='svn_ssh' data-url=''>SVN+SSH</a>
</div>
<div class='ui fluid right labeled small input download-url-panel'>
<input type="text" name="project_clone_url" id="project_clone_url" value="https://gitee.com/openeuler/docs.git" onclick="focus();select()" readonly="readonly" />
<div class='ui basic label'>
<div class='ui small basic orange button' data-clipboard-target='#project_clone_url' id='btn-copy-clone-url'>
复制
</div>
</div>
</div>
<div class='ui fluid right labeled warning-text forbid-warning-text'>

</div>

<hr>
<a class="ui fluid download link button" sa_evt="loginInform_show" sa_referrer_url="" sa_referrer_action="克隆/下载" sa_referrer_type="其他" href="javascript:void(0);"><i class='icon download'></i>
下载ZIP
</a><div class='download_repository_zip form modal tiny ui' id='unlanding-complaint-modal'>
<i class='iconfont icon-close close'></i>
<div class='header'>
登录提示
</div>
<div class='container actions'>
<div class='content'>
该操作需登录 Gitee 帐号，请先登录后再操作。
</div>
<div class='ui orange icon large button ok'>
立即登录
</div>
<div class='ui button blank cancel'>
没有帐号，去注册
</div>
</div>
</div>
<script>
  var $elm = $('.download');
  
  $elm.on('click', function() {
    var modals = $("#unlanding-complaint-modal.download_repository_zip");
    if (modals.length > 1) {
      modals.eq(0).modal('show');
    } else {
      modals.modal('show');
    }
  })
  $("#unlanding-complaint-modal.download_repository_zip").modal({
    onDeny: function() {
      window.location.href = "/signup?from=download_repository_zip";
    },
    onApprove: function() {
      window.location.href = "/login?from=download_repository_zip";
    }
  })
</script>

</div>
<script>
  (function() {
    var $btnClone, $btnCopy, $input, $panel;
  
    $btnClone = $('#btn-dl-or-clone');
  
    $panel = $('.git-project-download-panel');
  
    $input = $('#project_clone_url');
  
    $btnCopy = $('#btn-copy-clone-url');
  
    $btnClone.popup({
      on: 'click',
      hoverable: true,
      position: 'bottom center'
    });
  
    $panel.find('.menu > .item').on('click', function(e) {
      var $item, dataUrl;
      $item = $(this).addClass('active');
      $item.siblings().removeClass('active');
      dataUrl = $item.attr('data-url');
      if (dataUrl) {
        $panel.find('.download-url-panel').show();
        $input.val(dataUrl);
        $panel.find('.forbid-warning-text').html('');
      } else {
        $panel.find('.download-url-panel').hide();
        $panel.find('.forbid-warning-text').html($item.attr('data-text') || '');
      }
      return $.cookie('remote_way', $item.attr('data-type'), {
        expires: 365,
        path: '/'
      });
    }).filter('[data-type="' + ($.cookie('remote_way') || 'http') + '"]').trigger('click');
  
    new Clipboard($btnCopy[0]).on('success', function() {
      $btnCopy.popup({
        content: '已复制',
        position: 'right center',
        onHidden: function() {
          return $btnCopy.popup('destroy');
        }
      });
      return $btnCopy.popup('show');
    });
  
  }).call(this);
</script>

</div>
<div class='d-inline pull-right' id='git-project-root-actions'>
<script>
  $('.disabled-upload-readonly').popup({
    content: "只读目录不允许上传文件",
    className: {
      popup: 'ui popup',
    },
    position: 'bottom center',
  })
  $('.disabled-create-folder').popup({
    content: "只读目录不允许创建目录",
    className: {
      popup: 'ui popup',
    },
    position: 'bottom center',
  })
  $('.disabled-create-file').popup({
    content: "只读目录不允许创建文件",
    className: {
      popup: 'ui popup',
    },
    position: 'bottom center',
  })
  $('.disabled-upload-readonly').click(function() {
    return false
  })
  $('.disabled-create-folder').click(function() {
    return false
  })
  $('.disabled-create-file').click(function() {
    return false
  })
</script>
<style>
  .disabled-upload-readonly, .disabled-create-file, .disabled-create-folder {
    background-color: #dcddde !important;
    color: rgba(0, 0, 0, 0.4) !important;
    opacity: 0.3 !important;
    background-image: none !important;
    -webkit-box-shadow: none !important;
            box-shadow: none !important; }
</style>


</div>
<div class='breadcrumb_path path-breadcrumb-contrainer' id='git-project-breadcrumb'>
<div class='ui breadcrumb path project-path-breadcrumb' id='path-breadcrumb'>
<a data-direction="back" class="section repo-name" style="font-weight: bold" href="/openeuler/docs/tree/stable2-20.03_LTS_SP1">docs
</a><div class='divider'>
/
</div>
<strong>
<a data-direction="back" class="section" href="/openeuler/docs/tree/stable2-20.03_LTS_SP1/docs"><span class='cblue'>
docs
</span>
</a></strong>
<div class='divider'>
/
</div>
<strong>
<a data-direction="back" class="section" href="/openeuler/docs/tree/stable2-20.03_LTS_SP1/docs/zh"><span class='cblue'>
zh
</span>
</a></strong>
<div class='divider'>
/
</div>
<strong>
<a data-direction="back" class="section" href="/openeuler/docs/tree/stable2-20.03_LTS_SP1/docs/zh/docs"><span class='cblue'>
docs
</span>
</a></strong>
<div class='divider'>
/
</div>
<strong>
<a data-direction="back" class="section" href="/openeuler/docs/tree/stable2-20.03_LTS_SP1/docs/zh/docs/Virtualization"><span class='cblue'>
Virtualization
</span>
</a></strong>
<div class='divider'>
/
</div>
<strong>
LibcarePlus.md
</strong>
<i class='iconfont icon-clone' data-clipboard-text='docs/zh/docs/Virtualization/LibcarePlus.md' id='btn-copy-file-path'></i>
</div>
<style>
  #btn-copy-file-path {
    vertical-align: middle;
    cursor: pointer;
  }
</style>
<script>
  $btnCopy = $('#btn-copy-file-path')
  $btnCopy.popup({
    content: '复制路径'
  })
  
  if ($btnCopy[0]) {
    new Clipboard($btnCopy[0]).on('success', function() {
      $btnCopy.popup('destroy').popup({
        content: '已复制',
        on: 'manual'
      }).popup('show');
      setTimeout(function () {
        $btnCopy.popup('destroy').popup({
          content: '复制路径'
        });
      }, 2000)
    });
  }
</script>


</div>
<div class='ui horizontal list repo-action-list branches-tags' style='display: none;'>
<div class='item'>
<a class="ui blank button" href="/openeuler/docs/branches"><i class='iconfont icon-branches'></i>
分支 9
</a></div>
<div class='item mr-3'>
<a class="ui blank button" href="/openeuler/docs/tags"><i class='iconfont icon-tag'></i>
标签 4
</a></div>
</div>
</div>
<script>
  if(window.gon.locale == 'en')
    $('.branches-tags').css('margin-top', '12px')
</script>

<style>
  .ui.dropdown .menu > .header {
    text-transform: none; }
</style>
<script>
  $(function () {
    var $tip = $('#apk-download-tip');
    if (!$tip.length) {
      return;
    }
    $tip.find('.btn-close').on('click', function () {
      $tip.hide();
    });
  });
  (function(){
    function pathAutoRender() {
      var $parent = $('#git-project-bread'),
          $child = $('#git-project-bread').children('.ui.horizontal.list'),
          mainWidth = 0;
      $child.each(function (i,item) {
        mainWidth += $(item).width()
      });
      $('.breadcrumb.path.fork-path').remove();
      if (mainWidth > 995) {
        $('#path-breadcrumb').hide();
        $parent.append('<div class="ui breadcrumb path fork-path">' + $('#path-breadcrumb').html() + '<div/>')
      } else {
        $('#path-breadcrumb').show();
      }
    }
    window.pathAutoRender = pathAutoRender;
    pathAutoRender();
  })();
</script>

<div class='row column tree-holder' id='tree-holder'>
<div class='tree-content-holder' id='tree-content-holder'>
<div class='file_holder'>
<div class='file_title'>
<div class='blob-header-title'>
<div class='blob-description'>
<i class="iconfont icon-file"></i>
<span class='file_name' title='LibcarePlus.md'>
LibcarePlus.md
</span>
<small>10.91 KB</small>
</div>
<div class='options'><div class='ui mini buttons basic'>

<textarea name="blob_raw" id="blob_raw" style="display:none;">
# LibcarePlus&#x000A;&#x000A;- [概述](#概述)&#x000A;- [软硬件要求](#软硬件要求)&#x000A;- [注意事项和约束](#注意事项和约束)&#x000A;- [安装 LibcarePlus](#安装LibcarePlus)&#x000A;- [制作 LibcarePlus 热补丁](#制作_LibcarePlus_热补丁)&#x000A;- [应用 LibcarePlus 热补丁](#应用_LibcarePlus_热补丁)&#x000A;&#x000A;## 概述&#x000A;&#x000A;LibcarePlus 是一个用户态进程热补丁框架，可以在不重启进程的情况下对 Linux 系统上运行的目标进程进行热补丁操作。热补丁可以应用于 CVE 漏洞修复，也可以应用于不中断应用服务的紧急 bug 修复。&#x000A;&#x000A;## 软硬件要求&#x000A;&#x000A;在 openEuler 上使用 LibcarePlus，需要满足一定的软硬件要求：&#x000A;&#x000A;- 当前仅支持 x86 体系架构。&#x000A;&#x000A;- LibcarePlus 可以在任何支持安装 **libunwind**、 **elfutils** 以及 **binutils** 的 Linux 发行版系统上运行。但目前仅在 openEuler 20.03 LTS SP1 版本进行了验证。&#x000A;&#x000A;&#x000A;## 注意事项和约束&#x000A;&#x000A;使用 LibcarePlus，需遵循以下热补丁规范和约束：&#x000A;&#x000A;- 仅支持对 C 语言编写的代码，不支持汇编语言等。&#x000A;- 仅支持用户态程序，不支持动态库打补丁。&#x000A;- 代码文件名必须符合 C 语言标识符命名规范：由字母（A-Z,a-z）、数字 （0-9）、下划线“_”组成；并且首字符不能是数字，但可以是字母或者下划线；不能包含“-”、“$”等特殊符号。&#x000A;- 不支持增量补丁，即必须卸载原有补丁才能加载第二个补丁。 &#x000A;- 不支持补丁自动加载。 &#x000A;- 不支持补丁查询。 &#x000A;- 被打热补丁的目标函数的出参和入参不能增加和删除。&#x000A;- 静态函数补丁受限于系统中能找到该函数的符号表。&#x000A;- 动态库热补丁只能对调用这个动态库的进程打补丁。&#x000A;- 以下场景不支持热补丁:&#x000A;  - 死循环函数、不退出函数、inline 函数、初始化函数、NMI 中断处理函数&#x000A;  - 替换全局变量&#x000A;  - 修改头文件&#x000A;  - 数据结构成员变化（新增、删除、修改）&#x000A;  - 动态库、静态函数、静态变量&#x000A;  - 修改全局变量、TLS 变量、RCU 变量 &#x000A;  - 修改包含 __LINE__ ， __FILE__ 等gcc编译宏的 C 文件 &#x000A;  - 修改 intel 矢量汇编指令 &#x000A;&#x000A;&#x000A;&#x000A;## 安装 LibcarePlus&#x000A;&#x000A;### 安装软件依赖&#x000A;&#x000A;LibcarePlus 运行依赖于 **libunwind**、 **elfutils** 和 **binutils**，在配置了 yum 源的 openEuler 系统上，可以参考如下命令安装 LibcarePlus 的依赖软件。&#x000A;&#x000A;``` shell&#x000A;$ sudo yum install -y binutils elfutils elfutils-libelf-devel libunwind-devel&#x000A;```&#x000A;&#x000A;#### 安装 LibcarePlus&#x000A;&#x000A;```shell&#x000A;$ yum install LibcarePlus -y&#x000A;```&#x000A;&#x000A;查看安装是否成功：&#x000A;&#x000A;``` shell&#x000A;$ libcare-ctl -help&#x000A;usage: libcare-ctl [options] &lt;cmd&gt; [args]&#x000A;&#x000A;Options:&#x000A;  -v          - verbose mode&#x000A;  -h          - this message&#x000A;&#x000A;Commands:&#x000A;  patch  - apply patch to a user-space process&#x000A;  unpatch- unapply patch from a user-space process&#x000A;  info   - show info on applied patches&#x000A;  server - listen on a unix socket for commands&#x000A;```&#x000A;&#x000A;## 制作 LibcarePlus 热补丁&#x000A;&#x000A;### 概述&#x000A;&#x000A;LibcarePlus 支持如下方式制作热补丁：&#x000A;&#x000A;- 手动制作&#x000A;- 通过脚本制作&#x000A;&#x000A;手动制作热补丁的过程繁琐，对于代码量较大的工程，例如QEMU，手动制作热补丁极其困难。建议使用 LibcarePlus 自带脚本一键式地生成热补丁文件。&#x000A;&#x000A;#### 手动制作&#x000A;&#x000A;本节以原文件 foo.c 和补丁文件 bar.c 为例，给出手动制作热补丁的指导。&#x000A;&#x000A;1. 准备 C 语言编写的原文件和补丁文件。例如原文件 foo.c 和补丁文件 bar.c 。&#x000A;&#x000A;    &lt;details&gt;&#x000A;    &lt;summary&gt;点击展开 foo.c&lt;/summary&gt;&#x000A;    &lt;p&gt;&#x000A;&#x000A;    ``` c&#x000A;    // foo.c                                                                        &#x000A;    #include &lt;stdio.h&gt;&#x000A;    #include &lt;time.h&gt;&#x000A;&#x000A;    void print_hello(void)&#x000A;    {&#x000A;        printf(&quot;Hello world!\n&quot;);&#x000A;    }&#x000A;&#x000A;    int main(void)&#x000A;    {&#x000A;        while (1) {&#x000A;            print_hello();&#x000A;            sleep(1);&#x000A;        }&#x000A;    }&#x000A;    ```&#x000A;&#x000A;    &lt;/p&gt;&#x000A;    &lt;/details&gt;  &#x000A;&#x000A;    &lt;details&gt;&#x000A;    &lt;summary&gt;点击展开 bar.c&lt;/summary&gt;&#x000A;    &lt;p&gt;&#x000A;&#x000A;    ``` c&#x000A;    // bar.c                                                                                   &#x000A;    #include &lt;stdio.h&gt;&#x000A;    #include &lt;time.h&gt;&#x000A;                                                                                    &#x000A;    void print_hello(void)&#x000A;    {&#x000A;        printf(&quot;Hello world %s!\n&quot;, &quot;being patched&quot;);&#x000A;    }&#x000A;&#x000A;    int main(void)&#x000A;    {&#x000A;        while (1) {&#x000A;            print_hello();&#x000A;            sleep(1);&#x000A;        }&#x000A;    }&#x000A;    ```&#x000A;&#x000A;    &lt;/p&gt;&#x000A;    &lt;/details&gt; &#x000A;&#x000A;2. 编译得到原文件和补丁文件的汇编文件 **foo.s** 和 **bar.s**，参考命令如下：&#x000A;&#x000A;    ``` shell&#x000A;    $ gcc -S foo.c&#x000A;    $ gcc -S bar.c&#x000A;    $ ls&#x000A;    bar.c  bar.s  foo.c  foo.s&#x000A;    ```&#x000A;&#x000A;&#x000A;3.  使用 **kpatch_gensrc** 对比 foo.s 和 bar.s 差异，生成包含原文件的汇编内容和差异内容的 foobar.s，参考命令如下：&#x000A;&#x000A;    ``` shell&#x000A;    $ sed -i &#39;s/bar.c/foo.c/&#39; bar.s&#x000A;    $ kpatch_gensrc --os=rhel6 -i foo.s -i bar.s -o foobar.s --force-global&#x000A;    ```&#x000A;&#x000A;    由于 **kpatch_gensrc** 默认对同一 C 语言原文件进行对比，所以对比前需要使用 sed 命令将补丁汇编文件 bar.s 中的 bar.c 改为原文件名称 foo.c。随后调用 **kpatch_gensrc**，指定输入文件为 foo.s 与 bar.s，输出文件为 foobar.s。&#x000A;&#x000A;4. 编译原文件的汇编文件 foo.s 和生成的汇编文件 foobar.s，得到可执行文件 foo 和 foobar，参考命令如下：&#x000A;&#x000A;    ``` shell&#x000A;    $ gcc -o foo foo.s&#x000A;    $ gcc -o foobar foobar.s -Wl,-q&#x000A;    ```&#x000A;&#x000A;&#x000A;&#x000A;5. 利用 **kpatch_strip** 去除可执行程序 foo 和 foobar 的相同内容，保留制作热补丁所需要的内容。&#x000A;&#x000A;    ``` shell&#x000A;    $ kpatch_strip --strip foobar foobar.stripped&#x000A;    $ kpatch_strip --rel-fixup foo foobar.stripped&#x000A;    $ strip --strip-unneeded foobar.stripped&#x000A;    $ kpatch_strip --undo-link foo foobar.stripped&#x000A;    ```&#x000A;&#x000A;    上述命令中的各参数含义为：&#x000A;&#x000A;    - **--strip** 用于去除 foobar 中对于补丁制作无用的 section；&#x000A;    - **--rel-fixup** 用于修复补丁内所访问的变量以及函数的地址；&#x000A;    - **strip --strip-unneeded** 用于去除对于热补丁重定位操作无用的符号信息；&#x000A;    - **--undo-link** 用于将补丁内符号的地址从绝对地址更改为相对地址。&#x000A;&#x000A;6. 制作热补丁文件。&#x000A;&#x000A;   通过以上操作，已经得到了热补丁制作所需的主要内容。接下来需要使用 **kpatch_make** 将原可执行文件的 **Build ID** 以及 **kpatch_strip** 的输出文件 **foobar.stripped** 作为参数传递给 **kpatch_make**，最终生成热补丁文件，参考命令如下：&#x000A;   &#x000A;    ``` shell&#x000A;    $ str=$(readelf -n foo | grep &#39;Build ID&#39;)&#x000A;    $ substr=${str##* }&#x000A;    $ kpatch_make -b $substr foobar.stripped -o foo.kpatch&#x000A;    $ ls&#x000A;    bar.c  bar.s  foo  foobar  foobar.s  foobar.stripped  foo.c  foo.kpatch  foo.s&#x000A;    ```&#x000A;   &#x000A;   至此，就得到了最终的热补丁文件 foo.kpatch。&#x000A;&#x000A;#### 通过脚本制作&#x000A;&#x000A;本节介绍如何利用 LibcarePlus 自带的 **libcare-patch-make** 脚本制作热补丁文件，仍以原文件 foo.c 和补丁文件 bar.c 为例。&#x000A;&#x000A;1. 利用 diff 命令生成 foo.c 和 bar.c 的对比文件，命令如下所示:&#x000A;&#x000A;    ``` shell&#x000A;    $ diff -up foo.c bar.c &gt; foo.patch&#x000A;    ```&#x000A;&#x000A;    foo.patch 文件内容如下所示：&#x000A;&#x000A;    &lt;details&gt;&#x000A;    &lt;summary&gt;点击展开 foo.patch&lt;/summary&gt;&#x000A;    &lt;p&gt;&#x000A;&#x000A;&#x000A;    ``` diff&#x000A;    --- foo.c	2020-12-09 15:39:51.159632075 +0800&#x000A;    +++ bar.c	2020-12-09 15:40:03.818632220 +0800&#x000A;    @@ -1,10 +1,10 @@&#x000A;    -// foo.c&#x000A;    +// bar.c&#x000A;    #include &lt;stdio.h&gt;&#x000A;    #include &lt;time.h&gt;&#x000A;&#x000A;    void i_m_being_patched(void)&#x000A;    {&#x000A;    -    printf(&quot;i&#39;m unpatched!\n&quot;);&#x000A;    +    printf(&quot;you patched my %s\n&quot;, &quot;tralala&quot;);&#x000A;    }&#x000A;&#x000A;    int main(void)&#x000A;    ```&#x000A;&#x000A;    &lt;/p&gt;&#x000A;    &lt;/details&gt; &#x000A;&#x000A;&#x000A;2. 编写编译 foo.c 的 MakeFile 文件，具体如下所示：&#x000A;&#x000A;    &lt;details&gt;&#x000A;    &lt;summary&gt;点击展开 MakeFile&lt;/summary&gt;&#x000A;    &lt;p&gt;&#x000A;&#x000A;	``` makefile&#x000A;	all: foo&#x000A;	&#x000A;	foo: foo.c&#x000A;		$(CC) -o $@ $&lt;&#x000A;	&#x000A;	clean:&#x000A;		rm -f foo&#x000A;&#x000A;	install: foo&#x000A;		mkdir $$DESTDIR || :&#x000A;		cp foo $$DESTDIR&#x000A;	```&#x000A;&#x000A;    &lt;/p&gt;&#x000A;    &lt;/details&gt; &#x000A;&#x000A;&#x000A;3. 编写好 MakeFile 之后，直接调用 **libcare-patch-make** 即可。若 **libcare-patch-make** 询问选择哪个文件进行打补丁操作，输入原文件名即可，具体如下所示：&#x000A;&#x000A;    ``` shell&#x000A;    $ libcare-patch-make --clean foo.patch&#x000A;    rm -f foo&#x000A;    BUILDING ORIGINAL CODE&#x000A;    /usr/local/bin/libcare-cc -o foo foo.c&#x000A;    INSTALLING ORIGINAL OBJECTS INTO /libcareplus/test/lpmake&#x000A;    mkdir $DESTDIR || :&#x000A;    cp foo $DESTDIR&#x000A;    applying foo.patch...&#x000A;    can&#39;t find file to patch at input line 3&#x000A;    Perhaps you used the wrong -p or --strip option?&#x000A;    The text leading up to this was:&#x000A;    --------------------------&#x000A;    |--- foo.c	2020-12-10 09:43:04.445375845 +0800&#x000A;    |+++ bar.c	2020-12-10 09:48:36.778379648 +0800&#x000A;    --------------------------&#x000A;    File to patch: foo.c         &#x000A;    patching file foo.c&#x000A;    BUILDING PATCHED CODE&#x000A;    /usr/local/bin/libcare-cc -o foo foo.c&#x000A;    INSTALLING PATCHED OBJECTS INTO /libcareplus/test/.lpmaketmp/patched&#x000A;    mkdir $DESTDIR || :&#x000A;    cp foo $DESTDIR&#x000A;    MAKING PATCHES&#x000A;    Fixing up relocation printf@@GLIBC_2.2.5+fffffffffffffffc&#x000A;    Fixing up relocation print_hello+0&#x000A;    patch for /libcareplus/test/lpmake/foo is in /libcareplus/test/patchroot/700297b7bc56a11e1d5a6fb564c2a5bc5b282082.kpatch&#x000A;    ```&#x000A;&#x000A;    执行成功之后，输出显示：热补丁文件位于当前目录的 **patchroot** 目录下，可执行文件则在 **lpmake** 目录下。脚本生成的热补丁文件默认是采用 Build ID 作为热补丁文件的文件名。&#x000A;&#x000A;&#x000A;&#x000A;## 应用 LibcarePlus 热补丁&#x000A;&#x000A;本节以原文件 **foo.c** 和补丁文件 **bar.c** 为例，介绍 LibcarePlus 热补丁的应用指导。&#x000A;&#x000A;### 前期准备&#x000A;&#x000A;应用 LibcarePlus 热补丁之前，需要提前准备好原可执行程序 foo、以及热补丁文件 foo.kpatch。&#x000A;&#x000A;### 加载热补丁&#x000A;&#x000A;本节介绍应用 LibcarePlus 热补丁的具体流程。&#x000A;&#x000A;1. 首先在第一个 shell 窗口运行需要打补丁的可执行程序，如下所示：&#x000A;&#x000A;    ``` shell&#x000A;    $ ./lpmake/foo&#x000A;    Hello world!&#x000A;    Hello world!&#x000A;    Hello world!&#x000A;    ```&#x000A;&#x000A;2. 随后在第二个 shell 窗口运行 **libcare-ctl** 应用热补丁，命令如下所示：&#x000A;&#x000A;    ``` shell&#x000A;    $ libcare-ctl -v patch -p $(pidof foo) ./foo.kpatch&#x000A;    ```&#x000A;&#x000A;    若此时热补丁应用成功，第二个 shell 窗口会有如下输出：&#x000A;&#x000A;    ``` shell&#x000A;    1 patch hunk(s) have been successfully applied to PID &#39;10999&#39;&#x000A;    ```&#x000A;&#x000A;    而第一个 shell 窗口内运行的目标进程则会出现如下输出：&#x000A;&#x000A;    ``` shell&#x000A;    Hello world!&#x000A;    Hello world!&#x000A;    Hello world being patched!&#x000A;    Hello world being patched!&#x000A;    ```&#x000A;&#x000A;&#x000A;### 卸载热补丁&#x000A;&#x000A;本节介绍卸载 LibcarePlus 热补丁的具体流程。&#x000A;&#x000A;1. 在第二个 shell 窗口执行如下命令：&#x000A;&#x000A;    ``` shell&#x000A;    $ libcare-ctl unpatch -p $(pidof foo)&#x000A;    ```&#x000A;&#x000A;    此时若热补丁卸载成功，第二个 shell 窗口会有如下输出：&#x000A;&#x000A;    ``` shell&#x000A;    1 patch hunk(s) were successfully cancelled from PID &#39;10999&#39;&#x000A;    ```&#x000A;&#x000A;2. 第一个 shell 窗口内运行的目标进程则会出现如下输出：&#x000A;&#x000A;    ``` shell&#x000A;    Hello world being patched!&#x000A;    Hello world being patched!&#x000A;    Hello world!&#x000A;    Hello world!&#x000A;    ```&#x000A;</textarea>
<a class="ui button" id="copy-text" href="#">一键复制</a>
<a class="ui button edit-blob" title="只有登陆后才可以编辑" href="/openeuler/docs/edit/stable2-20.03_LTS_SP1/docs/zh/docs/Virtualization/LibcarePlus.md">编辑</a>
<a class="ui button web-ide" target="_blank" href="/-/ide/project/openeuler/docs/edit/stable2-20.03_LTS_SP1/-/docs/zh/docs/Virtualization/LibcarePlus.md">Web IDE</a>
<a class="ui button edit-raw" target="_blank" href="/openeuler/docs/raw/stable2-20.03_LTS_SP1/docs/zh/docs/Virtualization/LibcarePlus.md">原始数据</a>
<a class="ui button edit-blame" href="/openeuler/docs/blame/stable2-20.03_LTS_SP1/docs/zh/docs/Virtualization/LibcarePlus.md">按行查看</a>
<a class="ui button edit-history" href="/openeuler/docs/commits/stable2-20.03_LTS_SP1/docs/zh/docs/Virtualization/LibcarePlus.md">历史</a>
</div>
<script>
  "use strict";
  try {
    if((gon.wait_fork!=undefined && gon.wait_fork==true) || (gon.wait_fetch!=undefined && gon.wait_fetch==true)){
      $('.edit-blob').popup({content:"当前仓库正在后台处理中,暂时无法编辑", on: 'hover', delay: { show: 200, hide: 200 }});
      $('.edit-blob').click(function(e){
        e.preventDefault();
      })
    }
  
    var setUrl = function() {
      var params = window.location.search
      if (params==undefined || $.trim(params).length==0) return;
      $('span.options').children('.basic').find('a').each(function(index,ele){
        var origin_href = $(ele).attr('href');
        if (origin_href!="#" && origin_href.indexOf('?') == -1){
          $(ele).attr('href',origin_href+params);
        }
      });
    }
  
    setUrl();
  
    var clipboard = null,
        $btncopy  = $("#copy-text");
  
    clipboard = new Clipboard("#copy-text", {
      text: function(trigger) {
        return $("#blob_raw").val();
      }
    })
  
    clipboard.on('success', function(e) {
      $btncopy.popup('hide');
      $btncopy.popup('destroy');
      $btncopy.popup({content: '已复制', position: 'bottom center'});
      $btncopy.popup('show');
    })
  
    clipboard.on('error', function(e) {
      var giteeModal = new GiteeModalHelper({okText: '确定'});
      giteeModal.alert("一键复制", '复制失败，请手动复制');
    })
  
    $(function() {
      $btncopy.popup({
        content: '点击复制',
        position: 'bottom center'
      })
    })
  
  } catch (error) {
    console.log('blob/action error:' + error);
  }
  
  $('.disabled-edit-readonly').popup({
    content: "只读文件不可编辑",
    className: {
      popup: 'ui popup',
    },
    position: 'bottom center',
  })
  $('.disabled-edit-readonly, .disabled-edit-status').click(function() {
    return false
  })
  $('.has_tooltip').popup({
    position: 'top center'
  });
</script>
<style>
  .disabled-edit-readonly, .disabled-edit-status {
    background-color: #dcddde !important;
    color: rgba(0, 0, 0, 0.4) !important;
    opacity: 0.3 !important;
    background-image: none !important;
    -webkit-box-shadow: none !important;
            box-shadow: none !important;
    cursor: default !important; }
</style>
</div>
</div>
<div class='contributor-description'><span class='recent-commit' style='margin-top: 0.7rem'>
<a class="commit-author-link  js-popover-card " data-username="hurstsi" href="/hurstsi">HurstSi</a>
<span>提交于</span>
<span class='timeago commit-date' title='2021-08-24 00:47:14 +0800'>
2021-08-24 00:47
</span>
.
<a href="/openeuler/docs/commit/7369bfd8fea01d002a62d46a007cde7ecaa47c0d">低错 SP2-&gt;SP1</a>
</span>
</div>
</div>
<div class='clearfix'></div>
<div class='file_catalog'>
<div class='toggle'>
<i class='icon angle left'></i>
</div>
<div class='scroll-container'>
<div class='container'>
<div class='skeleton'>
<div class='line line1'></div>
<div class='line line2'></div>
<div class='line line3'></div>
<div class='line line1'></div>
<div class='line line2'></div>
<div class='line line3'></div>
</div>
</div>
</div>
</div>
<div class='file_content markdown-body'>
<h1>&#x000A;<a id="user-content-libcareplus" class="anchor" href="#libcareplus"></a>LibcarePlus</h1>&#x000A;<ul>&#x000A;<li><a href="#%E6%A6%82%E8%BF%B0">概述</a></li>&#x000A;<li><a href="#%E8%BD%AF%E7%A1%AC%E4%BB%B6%E8%A6%81%E6%B1%82">软硬件要求</a></li>&#x000A;<li><a href="#%E6%B3%A8%E6%84%8F%E4%BA%8B%E9%A1%B9%E5%92%8C%E7%BA%A6%E6%9D%9F">注意事项和约束</a></li>&#x000A;<li><a href="#%E5%AE%89%E8%A3%85LibcarePlus">安装 LibcarePlus</a></li>&#x000A;<li><a href="#%E5%88%B6%E4%BD%9C_LibcarePlus_%E7%83%AD%E8%A1%A5%E4%B8%81">制作 LibcarePlus 热补丁</a></li>&#x000A;<li><a href="#%E5%BA%94%E7%94%A8_LibcarePlus_%E7%83%AD%E8%A1%A5%E4%B8%81">应用 LibcarePlus 热补丁</a></li>&#x000A;</ul>&#x000A;<h2>&#x000A;<a id="user-content-概述" class="anchor" href="#%E6%A6%82%E8%BF%B0"></a>概述</h2>&#x000A;<p>LibcarePlus 是一个用户态进程热补丁框架，可以在不重启进程的情况下对 Linux 系统上运行的目标进程进行热补丁操作。热补丁可以应用于 CVE 漏洞修复，也可以应用于不中断应用服务的紧急 bug 修复。</p>&#x000A;<h2>&#x000A;<a id="user-content-软硬件要求" class="anchor" href="#%E8%BD%AF%E7%A1%AC%E4%BB%B6%E8%A6%81%E6%B1%82"></a>软硬件要求</h2>&#x000A;<p>在 openEuler 上使用 LibcarePlus，需要满足一定的软硬件要求：</p>&#x000A;<ul>&#x000A;<li>&#x000A;<p>当前仅支持 x86 体系架构。</p>&#x000A;</li>&#x000A;<li>&#x000A;<p>LibcarePlus 可以在任何支持安装 <strong>libunwind</strong>、 <strong>elfutils</strong> 以及 <strong>binutils</strong> 的 Linux 发行版系统上运行。但目前仅在 openEuler 20.03 LTS SP1 版本进行了验证。</p>&#x000A;</li>&#x000A;</ul>&#x000A;<h2>&#x000A;<a id="user-content-注意事项和约束" class="anchor" href="#%E6%B3%A8%E6%84%8F%E4%BA%8B%E9%A1%B9%E5%92%8C%E7%BA%A6%E6%9D%9F"></a>注意事项和约束</h2>&#x000A;<p>使用 LibcarePlus，需遵循以下热补丁规范和约束：</p>&#x000A;<ul>&#x000A;<li>仅支持对 C 语言编写的代码，不支持汇编语言等。</li>&#x000A;<li>仅支持用户态程序，不支持动态库打补丁。</li>&#x000A;<li>代码文件名必须符合 C 语言标识符命名规范：由字母（A-Z,a-z）、数字 （0-9）、下划线“_”组成；并且首字符不能是数字，但可以是字母或者下划线；不能包含“-”、“$”等特殊符号。</li>&#x000A;<li>不支持增量补丁，即必须卸载原有补丁才能加载第二个补丁。</li>&#x000A;<li>不支持补丁自动加载。</li>&#x000A;<li>不支持补丁查询。</li>&#x000A;<li>被打热补丁的目标函数的出参和入参不能增加和删除。</li>&#x000A;<li>静态函数补丁受限于系统中能找到该函数的符号表。</li>&#x000A;<li>动态库热补丁只能对调用这个动态库的进程打补丁。</li>&#x000A;<li>以下场景不支持热补丁:&#x000A;<ul>&#x000A;<li>死循环函数、不退出函数、inline 函数、初始化函数、NMI 中断处理函数</li>&#x000A;<li>替换全局变量</li>&#x000A;<li>修改头文件</li>&#x000A;<li>数据结构成员变化（新增、删除、修改）</li>&#x000A;<li>动态库、静态函数、静态变量</li>&#x000A;<li>修改全局变量、TLS 变量、RCU 变量</li>&#x000A;<li>修改包含 <strong>LINE</strong> ， <strong>FILE</strong> 等gcc编译宏的 C 文件</li>&#x000A;<li>修改 intel 矢量汇编指令</li>&#x000A;</ul>&#x000A;</li>&#x000A;</ul>&#x000A;<h2>&#x000A;<a id="user-content-安装-libcareplus" class="anchor" href="#%E5%AE%89%E8%A3%85-libcareplus"></a>安装 LibcarePlus</h2>&#x000A;<h3>&#x000A;<a id="user-content-安装软件依赖" class="anchor" href="#%E5%AE%89%E8%A3%85%E8%BD%AF%E4%BB%B6%E4%BE%9D%E8%B5%96"></a>安装软件依赖</h3>&#x000A;<p>LibcarePlus 运行依赖于 <strong>libunwind</strong>、 <strong>elfutils</strong> 和 <strong>binutils</strong>，在配置了 yum 源的 openEuler 系统上，可以参考如下命令安装 LibcarePlus 的依赖软件。</p>&#x000A;<div class="white"><div class="highlight"><pre><span id="LC1" class="line"><span class="nv">$ </span><span class="nb">sudo </span>yum <span class="nb">install</span> <span class="nt">-y</span> binutils elfutils elfutils-libelf-devel libunwind-devel</span></pre></div></div>&#x000A;<h4>&#x000A;<a id="user-content-安装-libcareplus-1" class="anchor" href="#%E5%AE%89%E8%A3%85-libcareplus-1"></a>安装 LibcarePlus</h4>&#x000A;<div class="white"><div class="highlight"><pre><span id="LC1" class="line"><span class="nv">$ </span>yum <span class="nb">install </span>LibcarePlus <span class="nt">-y</span></span></pre></div></div>&#x000A;<p>查看安装是否成功：</p>&#x000A;<div class="white"><div class="highlight"><pre><span id="LC1" class="line"><span class="nv">$ </span>libcare-ctl <span class="nt">-help</span></span>&#x000A;<span id="LC2" class="line">usage: libcare-ctl <span class="o">[</span>options] &lt;cmd&gt; <span class="o">[</span>args]</span>&#x000A;<span id="LC3" class="line"></span>&#x000A;<span id="LC4" class="line">Options:</span>&#x000A;<span id="LC5" class="line">  <span class="nt">-v</span>          - verbose mode</span>&#x000A;<span id="LC6" class="line">  <span class="nt">-h</span>          - this message</span>&#x000A;<span id="LC7" class="line"></span>&#x000A;<span id="LC8" class="line">Commands:</span>&#x000A;<span id="LC9" class="line">  patch  - apply patch to a user-space process</span>&#x000A;<span id="LC10" class="line">  unpatch- unapply patch from a user-space process</span>&#x000A;<span id="LC11" class="line">  info   - show info on applied patches</span>&#x000A;<span id="LC12" class="line">  server - listen on a unix socket <span class="k">for </span>commands</span></pre></div></div>&#x000A;<h2>&#x000A;<a id="user-content-制作-libcareplus-热补丁" class="anchor" href="#%E5%88%B6%E4%BD%9C-libcareplus-%E7%83%AD%E8%A1%A5%E4%B8%81"></a>制作 LibcarePlus 热补丁</h2>&#x000A;<h3>&#x000A;<a id="user-content-概述-1" class="anchor" href="#%E6%A6%82%E8%BF%B0-1"></a>概述</h3>&#x000A;<p>LibcarePlus 支持如下方式制作热补丁：</p>&#x000A;<ul>&#x000A;<li>手动制作</li>&#x000A;<li>通过脚本制作</li>&#x000A;</ul>&#x000A;<p>手动制作热补丁的过程繁琐，对于代码量较大的工程，例如QEMU，手动制作热补丁极其困难。建议使用 LibcarePlus 自带脚本一键式地生成热补丁文件。</p>&#x000A;<h4>&#x000A;<a id="user-content-手动制作" class="anchor" href="#%E6%89%8B%E5%8A%A8%E5%88%B6%E4%BD%9C"></a>手动制作</h4>&#x000A;<p>本节以原文件 foo.c 和补丁文件 bar.c 为例，给出手动制作热补丁的指导。</p>&#x000A;<ol>&#x000A;<li>&#x000A;<p>准备 C 语言编写的原文件和补丁文件。例如原文件 foo.c 和补丁文件 bar.c 。</p>&#x000A; <details>&#x000A; <summary>点击展开 foo.c</summary>&#x000A; <p>&#x000A;</p>&#x000A;<div class="white"><div class="highlight"><pre><span id="LC1" class="line"><span class="c1">// foo.c                                                                        </span></span>&#x000A;<span id="LC2" class="line"><span class="cp">#include &lt;stdio.h&gt;</span></span>&#x000A;<span id="LC3" class="line"><span class="cp">#include &lt;time.h&gt;</span></span>&#x000A;<span id="LC4" class="line"></span>&#x000A;<span id="LC5" class="line"><span class="kt">void</span> <span class="nf">print_hello</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></span>&#x000A;<span id="LC6" class="line"><span class="p">{</span></span>&#x000A;<span id="LC7" class="line">    <span class="n">printf</span><span class="p">(</span><span class="s">"Hello world!</span><span class="se">\n</span><span class="s">"</span><span class="p">);</span></span>&#x000A;<span id="LC8" class="line"><span class="p">}</span></span>&#x000A;<span id="LC9" class="line"></span>&#x000A;<span id="LC10" class="line"><span class="kt">int</span> <span class="nf">main</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></span>&#x000A;<span id="LC11" class="line"><span class="p">{</span></span>&#x000A;<span id="LC12" class="line">    <span class="k">while</span> <span class="p">(</span><span class="mi">1</span><span class="p">)</span> <span class="p">{</span></span>&#x000A;<span id="LC13" class="line">        <span class="n">print_hello</span><span class="p">();</span></span>&#x000A;<span id="LC14" class="line">        <span class="n">sleep</span><span class="p">(</span><span class="mi">1</span><span class="p">);</span></span>&#x000A;<span id="LC15" class="line">    <span class="p">}</span></span>&#x000A;<span id="LC16" class="line"><span class="p">}</span></span></pre></div></div>&#x000A; &#x000A; </details>  &#x000A; <details>&#x000A; <summary>点击展开 bar.c</summary>&#x000A; <p>&#x000A;</p>&#x000A;<div class="white"><div class="highlight"><pre><span id="LC1" class="line"><span class="c1">// bar.c                                                                                   </span></span>&#x000A;<span id="LC2" class="line"><span class="cp">#include &lt;stdio.h&gt;</span></span>&#x000A;<span id="LC3" class="line"><span class="cp">#include &lt;time.h&gt;</span></span>&#x000A;<span id="LC4" class="line">                                                                                </span>&#x000A;<span id="LC5" class="line"><span class="kt">void</span> <span class="nf">print_hello</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></span>&#x000A;<span id="LC6" class="line"><span class="p">{</span></span>&#x000A;<span id="LC7" class="line">    <span class="n">printf</span><span class="p">(</span><span class="s">"Hello world %s!</span><span class="se">\n</span><span class="s">"</span><span class="p">,</span> <span class="s">"being patched"</span><span class="p">);</span></span>&#x000A;<span id="LC8" class="line"><span class="p">}</span></span>&#x000A;<span id="LC9" class="line"></span>&#x000A;<span id="LC10" class="line"><span class="kt">int</span> <span class="nf">main</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></span>&#x000A;<span id="LC11" class="line"><span class="p">{</span></span>&#x000A;<span id="LC12" class="line">    <span class="k">while</span> <span class="p">(</span><span class="mi">1</span><span class="p">)</span> <span class="p">{</span></span>&#x000A;<span id="LC13" class="line">        <span class="n">print_hello</span><span class="p">();</span></span>&#x000A;<span id="LC14" class="line">        <span class="n">sleep</span><span class="p">(</span><span class="mi">1</span><span class="p">);</span></span>&#x000A;<span id="LC15" class="line">    <span class="p">}</span></span>&#x000A;<span id="LC16" class="line"><span class="p">}</span></span></pre></div></div>&#x000A; &#x000A; </details> &#x000A;</li>&#x000A;<li>&#x000A;<p>编译得到原文件和补丁文件的汇编文件 <strong>foo.s</strong> 和 <strong>bar.s</strong>，参考命令如下：</p>&#x000A;<div class="white"><div class="highlight"><pre><span id="LC1" class="line"><span class="nv">$ </span>gcc <span class="nt">-S</span> foo.c</span>&#x000A;<span id="LC2" class="line"><span class="nv">$ </span>gcc <span class="nt">-S</span> bar.c</span>&#x000A;<span id="LC3" class="line"><span class="nv">$ </span><span class="nb">ls</span></span>&#x000A;<span id="LC4" class="line">bar.c  bar.s  foo.c  foo.s</span></pre></div></div>&#x000A;</li>&#x000A;<li>&#x000A;<p>使用 <strong>kpatch_gensrc</strong> 对比 foo.s 和 bar.s 差异，生成包含原文件的汇编内容和差异内容的 foobar.s，参考命令如下：</p>&#x000A;<div class="white"><div class="highlight"><pre><span id="LC1" class="line"><span class="nv">$ </span><span class="nb">sed</span> <span class="nt">-i</span> <span class="s1">'s/bar.c/foo.c/'</span> bar.s</span>&#x000A;<span id="LC2" class="line"><span class="nv">$ </span>kpatch_gensrc <span class="nt">--os</span><span class="o">=</span>rhel6 <span class="nt">-i</span> foo.s <span class="nt">-i</span> bar.s <span class="nt">-o</span> foobar.s <span class="nt">--force-global</span></span></pre></div></div>&#x000A;<p>由于 <strong>kpatch_gensrc</strong> 默认对同一 C 语言原文件进行对比，所以对比前需要使用 sed 命令将补丁汇编文件 bar.s 中的 bar.c 改为原文件名称 foo.c。随后调用 <strong>kpatch_gensrc</strong>，指定输入文件为 foo.s 与 bar.s，输出文件为 foobar.s。</p>&#x000A;</li>&#x000A;<li>&#x000A;<p>编译原文件的汇编文件 foo.s 和生成的汇编文件 foobar.s，得到可执行文件 foo 和 foobar，参考命令如下：</p>&#x000A;<div class="white"><div class="highlight"><pre><span id="LC1" class="line"><span class="nv">$ </span>gcc <span class="nt">-o</span> foo foo.s</span>&#x000A;<span id="LC2" class="line"><span class="nv">$ </span>gcc <span class="nt">-o</span> foobar foobar.s <span class="nt">-Wl</span>,-q</span></pre></div></div>&#x000A;</li>&#x000A;<li>&#x000A;<p>利用 <strong>kpatch_strip</strong> 去除可执行程序 foo 和 foobar 的相同内容，保留制作热补丁所需要的内容。</p>&#x000A;<div class="white"><div class="highlight"><pre><span id="LC1" class="line"><span class="nv">$ </span>kpatch_strip <span class="nt">--strip</span> foobar foobar.stripped</span>&#x000A;<span id="LC2" class="line"><span class="nv">$ </span>kpatch_strip <span class="nt">--rel-fixup</span> foo foobar.stripped</span>&#x000A;<span id="LC3" class="line"><span class="nv">$ </span>strip <span class="nt">--strip-unneeded</span> foobar.stripped</span>&#x000A;<span id="LC4" class="line"><span class="nv">$ </span>kpatch_strip <span class="nt">--undo-link</span> foo foobar.stripped</span></pre></div></div>&#x000A;<p>上述命令中的各参数含义为：</p>&#x000A;<ul>&#x000A;<li>&#x000A;<strong>--strip</strong> 用于去除 foobar 中对于补丁制作无用的 section；</li>&#x000A;<li>&#x000A;<strong>--rel-fixup</strong> 用于修复补丁内所访问的变量以及函数的地址；</li>&#x000A;<li>&#x000A;<strong>strip --strip-unneeded</strong> 用于去除对于热补丁重定位操作无用的符号信息；</li>&#x000A;<li>&#x000A;<strong>--undo-link</strong> 用于将补丁内符号的地址从绝对地址更改为相对地址。</li>&#x000A;</ul>&#x000A;</li>&#x000A;<li>&#x000A;<p>制作热补丁文件。</p>&#x000A;<p>通过以上操作，已经得到了热补丁制作所需的主要内容。接下来需要使用 <strong>kpatch_make</strong> 将原可执行文件的 <strong>Build ID</strong> 以及 <strong>kpatch_strip</strong> 的输出文件 <strong>foobar.stripped</strong> 作为参数传递给 <strong>kpatch_make</strong>，最终生成热补丁文件，参考命令如下：</p>&#x000A;<div class="white"><div class="highlight"><pre><span id="LC1" class="line"><span class="nv">$ str</span><span class="o">=</span><span class="si">$(</span>readelf <span class="nt">-n</span> foo | <span class="nb">grep</span> <span class="s1">'Build ID'</span><span class="si">)</span></span>&#x000A;<span id="LC2" class="line"><span class="nv">$ substr</span><span class="o">=</span><span class="k">${</span><span class="nv">str</span><span class="p">##* </span><span class="k">}</span></span>&#x000A;<span id="LC3" class="line"><span class="nv">$ </span>kpatch_make <span class="nt">-b</span> <span class="nv">$substr</span> foobar.stripped <span class="nt">-o</span> foo.kpatch</span>&#x000A;<span id="LC4" class="line"><span class="nv">$ </span><span class="nb">ls</span></span>&#x000A;<span id="LC5" class="line">bar.c  bar.s  foo  foobar  foobar.s  foobar.stripped  foo.c  foo.kpatch  foo.s</span></pre></div></div>&#x000A;<p>至此，就得到了最终的热补丁文件 foo.kpatch。</p>&#x000A;</li>&#x000A;</ol>&#x000A;<h4>&#x000A;<a id="user-content-通过脚本制作" class="anchor" href="#%E9%80%9A%E8%BF%87%E8%84%9A%E6%9C%AC%E5%88%B6%E4%BD%9C"></a>通过脚本制作</h4>&#x000A;<p>本节介绍如何利用 LibcarePlus 自带的 <strong>libcare-patch-make</strong> 脚本制作热补丁文件，仍以原文件 foo.c 和补丁文件 bar.c 为例。</p>&#x000A;<ol>&#x000A;<li>&#x000A;<p>利用 diff 命令生成 foo.c 和 bar.c 的对比文件，命令如下所示:</p>&#x000A;<div class="white"><div class="highlight"><pre><span id="LC1" class="line"><span class="nv">$ </span>diff <span class="nt">-up</span> foo.c bar.c <span class="o">&gt;</span> foo.patch</span></pre></div></div>&#x000A;<p>foo.patch 文件内容如下所示：</p>&#x000A; <details>&#x000A; <summary>点击展开 foo.patch</summary>&#x000A; <p>&#x000A;</p>&#x000A;<div class="white"><div class="highlight"><pre><span id="LC1" class="line"><span class="gd">--- foo.c	2020-12-09 15:39:51.159632075 +0800</span></span>&#x000A;<span id="LC2" class="line"><span class="gi">+++ bar.c	2020-12-09 15:40:03.818632220 +0800</span></span>&#x000A;<span id="LC3" class="line"><span class="p">@@ -1,10 +1,10 @@</span></span>&#x000A;<span id="LC4" class="line"><span class="gd">-// foo.c</span></span>&#x000A;<span id="LC5" class="line"><span class="gi">+// bar.c</span></span>&#x000A;<span id="LC6" class="line"><span class="err">#include</span> &lt;stdio.h&gt;</span>&#x000A;<span id="LC7" class="line"><span class="err">#include</span> &lt;time.h&gt;</span>&#x000A;<span id="LC8" class="line"></span>&#x000A;<span id="LC9" class="line">void i_m_being_patched(void)</span>&#x000A;<span id="LC10" class="line"><span class="err">{</span></span>&#x000A;<span id="LC11" class="line">-    printf("i'm unpatched!\n");</span>&#x000A;<span id="LC12" class="line"><span class="gi">+    printf("you patched my %s\n", "tralala");</span></span>&#x000A;<span id="LC13" class="line"><span class="err">}</span></span>&#x000A;<span id="LC14" class="line"></span>&#x000A;<span id="LC15" class="line"><span class="p">int main(void)</span></span></pre></div></div>&#x000A; &#x000A; </details> &#x000A;</li>&#x000A;<li>&#x000A;<p>编写编译 foo.c 的 MakeFile 文件，具体如下所示：</p>&#x000A; <details>&#x000A; <summary>点击展开 MakeFile</summary>&#x000A; <p>&#x000A;</p>&#x000A;<div class="white"><div class="highlight"><pre><span id="LC1" class="line"><span class="nl">all</span><span class="o">:</span> <span class="nf">foo</span></span>&#x000A;<span id="LC2" class="line"></span>&#x000A;<span id="LC3" class="line"><span class="nl">foo</span><span class="o">:</span> <span class="nf">foo.c</span></span>&#x000A;<span id="LC4" class="line">	<span class="nv">$(CC)</span> <span class="nt">-o</span> <span class="nv">$@</span> <span class="nv">$&lt;</span></span>&#x000A;<span id="LC5" class="line"></span>&#x000A;<span id="LC6" class="line"><span class="nl">clean</span><span class="o">:</span></span>&#x000A;<span id="LC7" class="line">	<span class="nb">rm</span> <span class="nt">-f</span> foo</span>&#x000A;<span id="LC8" class="line"></span>&#x000A;<span id="LC9" class="line"><span class="nl">install</span><span class="o">:</span> <span class="nf">foo</span></span>&#x000A;<span id="LC10" class="line">	<span class="nb">mkdir</span> <span class="nv">$$</span>DESTDIR <span class="o">||</span> :</span>&#x000A;<span id="LC11" class="line">	<span class="nb">cp </span>foo <span class="nv">$$</span>DESTDIR</span></pre></div></div>&#x000A; &#x000A; </details> &#x000A;</li>&#x000A;<li>&#x000A;<p>编写好 MakeFile 之后，直接调用 <strong>libcare-patch-make</strong> 即可。若 <strong>libcare-patch-make</strong> 询问选择哪个文件进行打补丁操作，输入原文件名即可，具体如下所示：</p>&#x000A;<div class="white"><div class="highlight"><pre><span id="LC1" class="line"><span class="nv">$ </span>libcare-patch-make <span class="nt">--clean</span> foo.patch</span>&#x000A;<span id="LC2" class="line"><span class="nb">rm</span> <span class="nt">-f</span> foo</span>&#x000A;<span id="LC3" class="line">BUILDING ORIGINAL CODE</span>&#x000A;<span id="LC4" class="line">/usr/local/bin/libcare-cc <span class="nt">-o</span> foo foo.c</span>&#x000A;<span id="LC5" class="line">INSTALLING ORIGINAL OBJECTS INTO /libcareplus/test/lpmake</span>&#x000A;<span id="LC6" class="line"><span class="nb">mkdir</span> <span class="nv">$DESTDIR</span> <span class="o">||</span> :</span>&#x000A;<span id="LC7" class="line"><span class="nb">cp </span>foo <span class="nv">$DESTDIR</span></span>&#x000A;<span id="LC8" class="line">applying foo.patch...</span>&#x000A;<span id="LC9" class="line">can<span class="s1">'t find file to patch at input line 3</span></span>&#x000A;<span id="LC10" class="line"><span class="s1">Perhaps you used the wrong -p or --strip option?</span></span>&#x000A;<span id="LC11" class="line"><span class="s1">The text leading up to this was:</span></span>&#x000A;<span id="LC12" class="line"><span class="s1">--------------------------</span></span>&#x000A;<span id="LC13" class="line"><span class="s1">|--- foo.c	2020-12-10 09:43:04.445375845 +0800</span></span>&#x000A;<span id="LC14" class="line"><span class="s1">|+++ bar.c	2020-12-10 09:48:36.778379648 +0800</span></span>&#x000A;<span id="LC15" class="line"><span class="s1">--------------------------</span></span>&#x000A;<span id="LC16" class="line"><span class="s1">File to patch: foo.c         </span></span>&#x000A;<span id="LC17" class="line"><span class="s1">patching file foo.c</span></span>&#x000A;<span id="LC18" class="line"><span class="s1">BUILDING PATCHED CODE</span></span>&#x000A;<span id="LC19" class="line"><span class="s1">/usr/local/bin/libcare-cc -o foo foo.c</span></span>&#x000A;<span id="LC20" class="line"><span class="s1">INSTALLING PATCHED OBJECTS INTO /libcareplus/test/.lpmaketmp/patched</span></span>&#x000A;<span id="LC21" class="line"><span class="s1">mkdir $DESTDIR || :</span></span>&#x000A;<span id="LC22" class="line"><span class="s1">cp foo $DESTDIR</span></span>&#x000A;<span id="LC23" class="line"><span class="s1">MAKING PATCHES</span></span>&#x000A;<span id="LC24" class="line"><span class="s1">Fixing up relocation printf@@GLIBC_2.2.5+fffffffffffffffc</span></span>&#x000A;<span id="LC25" class="line"><span class="s1">Fixing up relocation print_hello+0</span></span>&#x000A;<span id="LC26" class="line"><span class="s1">patch for /libcareplus/test/lpmake/foo is in /libcareplus/test/patchroot/700297b7bc56a11e1d5a6fb564c2a5bc5b282082.kpatch</span></span></pre></div></div>&#x000A;<p>执行成功之后，输出显示：热补丁文件位于当前目录的 <strong>patchroot</strong> 目录下，可执行文件则在 <strong>lpmake</strong> 目录下。脚本生成的热补丁文件默认是采用 Build ID 作为热补丁文件的文件名。</p>&#x000A;</li>&#x000A;</ol>&#x000A;<h2>&#x000A;<a id="user-content-应用-libcareplus-热补丁" class="anchor" href="#%E5%BA%94%E7%94%A8-libcareplus-%E7%83%AD%E8%A1%A5%E4%B8%81"></a>应用 LibcarePlus 热补丁</h2>&#x000A;<p>本节以原文件 <strong>foo.c</strong> 和补丁文件 <strong>bar.c</strong> 为例，介绍 LibcarePlus 热补丁的应用指导。</p>&#x000A;<h3>&#x000A;<a id="user-content-前期准备" class="anchor" href="#%E5%89%8D%E6%9C%9F%E5%87%86%E5%A4%87"></a>前期准备</h3>&#x000A;<p>应用 LibcarePlus 热补丁之前，需要提前准备好原可执行程序 foo、以及热补丁文件 foo.kpatch。</p>&#x000A;<h3>&#x000A;<a id="user-content-加载热补丁" class="anchor" href="#%E5%8A%A0%E8%BD%BD%E7%83%AD%E8%A1%A5%E4%B8%81"></a>加载热补丁</h3>&#x000A;<p>本节介绍应用 LibcarePlus 热补丁的具体流程。</p>&#x000A;<ol>&#x000A;<li>&#x000A;<p>首先在第一个 shell 窗口运行需要打补丁的可执行程序，如下所示：</p>&#x000A;<div class="white"><div class="highlight"><pre><span id="LC1" class="line"><span class="nv">$ </span>./lpmake/foo</span>&#x000A;<span id="LC2" class="line">Hello world!</span>&#x000A;<span id="LC3" class="line">Hello world!</span>&#x000A;<span id="LC4" class="line">Hello world!</span></pre></div></div>&#x000A;</li>&#x000A;<li>&#x000A;<p>随后在第二个 shell 窗口运行 <strong>libcare-ctl</strong> 应用热补丁，命令如下所示：</p>&#x000A;<div class="white"><div class="highlight"><pre><span id="LC1" class="line"><span class="nv">$ </span>libcare-ctl <span class="nt">-v</span> patch <span class="nt">-p</span> <span class="si">$(</span>pidof foo<span class="si">)</span> ./foo.kpatch</span></pre></div></div>&#x000A;<p>若此时热补丁应用成功，第二个 shell 窗口会有如下输出：</p>&#x000A;<div class="white"><div class="highlight"><pre><span id="LC1" class="line">1 patch hunk<span class="o">(</span>s<span class="o">)</span> have been successfully applied to PID <span class="s1">'10999'</span></span></pre></div></div>&#x000A;<p>而第一个 shell 窗口内运行的目标进程则会出现如下输出：</p>&#x000A;<div class="white"><div class="highlight"><pre><span id="LC1" class="line">Hello world!</span>&#x000A;<span id="LC2" class="line">Hello world!</span>&#x000A;<span id="LC3" class="line">Hello world being patched!</span>&#x000A;<span id="LC4" class="line">Hello world being patched!</span></pre></div></div>&#x000A;</li>&#x000A;</ol>&#x000A;<h3>&#x000A;<a id="user-content-卸载热补丁" class="anchor" href="#%E5%8D%B8%E8%BD%BD%E7%83%AD%E8%A1%A5%E4%B8%81"></a>卸载热补丁</h3>&#x000A;<p>本节介绍卸载 LibcarePlus 热补丁的具体流程。</p>&#x000A;<ol>&#x000A;<li>&#x000A;<p>在第二个 shell 窗口执行如下命令：</p>&#x000A;<div class="white"><div class="highlight"><pre><span id="LC1" class="line"><span class="nv">$ </span>libcare-ctl unpatch <span class="nt">-p</span> <span class="si">$(</span>pidof foo<span class="si">)</span></span></pre></div></div>&#x000A;<p>此时若热补丁卸载成功，第二个 shell 窗口会有如下输出：</p>&#x000A;<div class="white"><div class="highlight"><pre><span id="LC1" class="line">1 patch hunk<span class="o">(</span>s<span class="o">)</span> were successfully cancelled from PID <span class="s1">'10999'</span></span></pre></div></div>&#x000A;</li>&#x000A;<li>&#x000A;<p>第一个 shell 窗口内运行的目标进程则会出现如下输出：</p>&#x000A;<div class="white"><div class="highlight"><pre><span id="LC1" class="line">Hello world being patched!</span>&#x000A;<span id="LC2" class="line">Hello world being patched!</span>&#x000A;<span id="LC3" class="line">Hello world!</span>&#x000A;<span id="LC4" class="line">Hello world!</span></pre></div></div>&#x000A;</li>&#x000A;</ol></div>
<script>
  window.Gitee.initReadmeCatalog();
  toMathMlCode('','markdown-body');
  $('.file_content a, .catalog-li a.anchor').click(function () {
    var anchor = $(this).attr('href')
    window.location.hash = anchor
  })
</script>

</div>
</div>
<div class='tree_progress'></div>
<div class='ui small modal' id='modal-linejump'>
<div class='ui custom form content'>
<div class='field'>
<div class='ui right action input'>
<input placeholder='跳转至某一行...' type='number'>
<div class='ui orange button'>
跳转
</div>
</div>
</div>
</div>
</div>


<div class='row column inner-comment' id='blob-comment'>
<input type="hidden" name="comment_path" id="comment_path" value="docs/zh/docs/Virtualization/LibcarePlus.md" />
<div class='tree-comments'>
<h3 id='tree_comm_title'>
评论
(
<span class='comments-count'>
0
</span>
)
</h3>
<div class='ui threaded comments middle aligned' id='notes-list'></div>
<input type="hidden" name="ajax_add_note_id" id="ajax_add_note_id" />
<div class='text-center'>
<div class='tip-loading' style='display: none'>
<div class='ui active mini inline loader'></div>
正在加载...
</div>
</div>
</div>
<script>
  "use strict";
  $(function(){
    var page = 1
    var commentsCount = 0
    var $container = $('.tree-comments')
    var $comments = $container.find('.ui.comments')
    var $tipLoading = $container.find('.tip-loading')
    var $btnLoad = $container.find('.btn-load-more')
    var noteAnchor = new Gitee.NoteAnchor({ defaultAnchor: '#tree_comm_title' })
  
    if (commentsCount < 1) {
      return;
    }
  
    var path;
    if ($('#comment_path').val() === '') {
      path = '/';
    } else {
      path = $('#comment_path').val();
    }
  
    function loadComments () {
      $btnLoad.hide();
      $tipLoading.show();
      $.ajax({
        url: '/openeuler/docs/comment_list',
        data: {
          page: page,
          path: path
        },
        success: function(data) {
          var err;
          try {
            $tipLoading.hide();
            $btnLoad.show();
            if (data.status !== 0) {
              $btnLoad.text('无更多评论')
              return $btnLoad.prop('disabled', true).addClass('disabled');
            } else {
              TreeComment.CommentListHandler(data);
              page += 1;
              if (data.comments_count < 10) {
                $('#ajax_add_note_id').val('');
                $btnLoad.text('无更多评论')
                $btnLoad.prop('disabled', true).addClass('disabled');
              }
              // osctree can not load script
              $comments.find('.timeago').timeago();
              $comments.find('.commenter-role-label').popup();
              noteAnchor.locate();
              toMathMlCode('', 'comments');
              return $('.markdown-body pre code').each(function(i, block) {
                return hljs.highlightBlock(block);
              });
            }
          } catch (error) {
            err = error;
            return console.log('loadComments error:' + err);
          }
        }
      });
    };
  
  
    function checkLoad () {
      var listTop, top;
      top = $(window).scrollTop();
      listTop = $container.offset().top;
      if (listTop >= top && listTop < top + $(window).height()) {
        $(window).off('scroll', checkLoad);
        return loadComments();
      }
    };
  
    $btnLoad.on('click', loadComments);
    loadComments()
  })
</script>

</div>
<div class='inner-comment-box' id='comment-box'>
<p>
你可以在<a href="/login">登录</a>后，发表评论
</p>

</div>

<div class='complaint'>
<div class='ui modal small form' id='landing-comments-complaint-modal'>
<i class='iconfont icon-close close'></i>
<div class='header'>
举报
</div>
<div class='content'>
<div class='appeal-success-tip hide'>
<i class='iconfont icon-ic_msg_success'></i>
<div class='appeal-success-text'>
举报成功
</div>
<span>
我们将于2个工作日内通过站内信反馈结果给你！
</span>
</div>
<div class='appeal-tip'>
请认真填写举报原因，尽可能描述详细。
</div>
<div class='ui form appeal-form'>
<div class='inline field'>
<label class='left-part appeal-type-wrap'>
举报类型
</label>
<div class='ui dropdown selection' id='appeal-comments-types'>
<div class='text default'>
请选择举报类型
</div>
<i class='dropdown icon'></i>
<div class='menu'></div>
</div>
</div>
<div class='inline field'>
<label class='left-part'>
举报原因
</label>
<textarea class='appeal-reason' id='appeal-comment-reason' name='msg' placeholder='请说明举报原因' rows='3'></textarea>
</div>
<div class='ui message callback-msg hide'></div>
<div class='ui small error text message exceeded-size-tip'></div>
</div>
</div>
<div class='actions'>
<div class='ui button blank cancel'>
取消
</div>
<div class='ui orange icon button disabled ok' id='complaint-comment-confirm'>
发送
</div>
</div>
</div>
<script>
  var $complaintCommentsModal = $('#landing-comments-complaint-modal'),
      $complainCommentType = $complaintCommentsModal.find('#appeal-comments-types'),
      $complaintModalTip = $complaintCommentsModal.find('.callback-msg'),
      $complaintCommentsContent = $complaintCommentsModal.find('.appeal-reason'),
      $complaintCommentBtn = $complaintCommentsModal.find('#complaint-comment-confirm'),
      complaintSending = false,
      initedCommentsType = false;
  
  function initCommentsTypeList() {
    if (!initedCommentsType) {
      $.ajax({
        url: "/appeals/fetch_types",
        method: 'get',
        data: {'type': 'comment'},
        success: function (data) {
          var result = '';
          for (var i = 0; i < data.length; i++) {
            result = result + "<div class='item' data-value='" + data[i].id + "'>" + data[i].name + "</div>";
          }
          $complainCommentType.find('.menu').html(result);
        }
      });
      $complainCommentType.dropdown({showOnFocus: false});
      initedCommentsType = true;
    }
  }
  $complainCommentType.on('click', function() {
    $complaintCommentsModal.modal({
      autofocus: false,
      onApprove: function() {
        return false;
      },
      onHidden: function() {
        restoreCommonentDefault();
      }
    }).modal('show');
  });
  
  $complaintCommentsContent.on('change keyup', function(e) {
    var content = $(this).val();
    if ($.trim(content).length > 0 && $complainCommentType.dropdown('get value').length > 0 ) {
      $complaintCommentBtn.removeClass('disabled');
      return;
    }
    $complaintCommentBtn.addClass('disabled');
  });
  
  
  $complainCommentType.dropdown({
    showOnFocus: false,
    onChange: function(value, text, $selectedItem) {
      if (value.length > 0 && $.trim($complaintCommentsContent.val()).length > 0) {
        $complaintCommentBtn.removeClass('disabled');
        return
      }
      $complaintCommentBtn.addClass('disabled');
    }
  });
  
  function restoreCommonentDefault() {
    $complainCommentType.dropdown('restore defaults');
    $complaintCommentsContent.val('');
    $('.exceeded-size-tip').text('').hide();
    $complaintModalTip.text('').hide();
    setTimeout(function() {
      setCommentSendTip(false);
    }, 1500);
  }
  
  $complaintCommentBtn.on('click',function(e){
    var reason = $complaintCommentsContent.val();
    var appealableId = $('#landing-comments-complaint-modal').attr('data-id');
    if (complaintSending) {
      return;
    }
    var appealType = $complainCommentType.dropdown('get value');
    var formData = new FormData();
    formData.append('appeal_type_id', appealType);
    formData.append('reason', reason);
    formData.append('appeal_type','Note');
    formData.append('target_id',appealableId);
    $.ajax({
      type: 'POST',
      url: "/appeals",
      cache: false,
      contentType: false,
      processData: false,
      data: formData,
      beforeSend: function() {
        setCommentSendStatus(true);
      },
      success: function(res) {
        if (res.status == 200) {
          setCommentSendTip(true);
          setTimeout(function() {
            $complaintCommentsModal.modal('hide');
            restoreCommonentDefault();
          }, 3000);
        }
        setCommentSendStatus(false);
      },
      error: function(err) {
        showCommonTips(err.responseJSON.message, 'error');
        setCommentSendStatus(false);
      }
    })
  });
  
  function showCommonTips(text, type) {
    $complaintModalTip.text(text).show();
    if (type == 'error') {
      $complaintModalTip.removeClass('success').addClass('error');
    } else {
      $complaintModalTip.removeClass('error').addClass('success');
    }
  }
  
  function setCommentSendStatus(value) {
    complaintSending = value;
    if (complaintSending) {
      $complaintCommentBtn.addClass('loading');
      $complaintCommentsContent.attr('readonly', true);
      $complainCommentType.attr('readonly', true);
    } else {
      $complaintCommentBtn.removeClass('loading');
      $complaintCommentsContent.attr('readonly', false);
      $complainCommentType.attr('readonly', false);
    }
  }
  
  function setCommentSendTip(value) {
    if (value) {
      $('.appeal-success-tip').removeClass('hide');
      $('.appeal-tip').addClass('hide');
      $('.appeal-form').addClass('hide');
      $('#landing-comments-complaint-modal .actions').addClass('hide');
    } else {
      $('.appeal-success-tip').addClass('hide');
      $('.appeal-tip').removeClass('hide');
      $('.appeal-form').removeClass('hide');
      $('#landing-comments-complaint-modal .actions').removeClass('hide');
    }
  }
</script>

</div>
<script>
  "use strict";
  $('.js-check-star').checkbox('set unchecked')
</script>

</div>
</div>
</div>
<div class='four wide column' style='display: none;'>
<div class='project__right-side'>
<div class='side-item intro'>
<div class='header'>
<h4>简介</h4>
</div>
<div class='content'>
<span class='git-project-desc-text'>This is openEuler documentation repository,</span>
<a class='hide spread' href='javascript:void(0);'>
展开
<i class='caret down icon'></i>
</a>
<a class='retract hide' href='javascript:void(0);'>
收起
<i class='caret up icon'></i>
</a>
<div class='intro-list'>
<div class='blank d-flex d-flex-between dropdown item js-project-label_show label-list-line-feed project-label-list ui' data-labels='[]' data-url='/openeuler/docs/update_description'>
<div class='mixed-label'>
</div>

<div class='default'>暂无标签</div>
</div>
<div class='hide item'>
<i class='iconfont icon-link'></i>
<span class='git-project-homepage'>
<a rel="nofollow" id="homepage" target="_blank" href=""></a>
</span>
</div>

<div class='item'>
<i class='iconfont icon-licence'></i>
<a target="_blank" id="license-popup" href="/openeuler/docs/blob/master/LICENSE">CC-BY-SA-4.0</a>
<div class='ui popup dark'>使用 CC-BY-SA-4.0 开源许可协议</div>
</div>
</div>
</div>
<div class='content intro-form'>
<div class='ui small input'>
<textarea name='project[description]' placeholder='描述' rows='5'></textarea>
</div>
<div class='ui small input'>
<input data-regex-value='(^$)|(^(http|https):\/\/(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5]).*)|(^(http|https):\/\/[a-zA-Z0-9]+([_\-\.]{1}[a-zA-Z0-9]+)*\.[a-zA-Z]{2,10}(:[0-9]{1,10})?(\?.*)?(\/.*)?$)' name='project[homepage]' placeholder='主页(eg: https://gitee.com)' type='text'>
</div>
<button class='ui orange button mt-1 btn-save'>
保存更改
</button>
<div class='ui blank button btn-cancel-edit'>
取消
</div>
</div>
</div>
<div class='side-item release'>
<div class='header'>
<h4>发行版</h4>
</div>
<div class='content'>
<span class='text-muted'>
暂无发行版
</span>
</div>
</div>
<div class='side-item radar'>
<div class='header mb-1'>
<h4 class='limit-length'>docs</h4>
<a class="ui link button radar-qa" href="javascript:void(0);"><i class='iconfont icon-help-circle'></i>
</a></div>
<div class='content'>
<div data-url='/openeuler/docs/project_radars' id='metrics-radar'>
<div class='wrap skeleton'>
<div class='total-score hide'>
<div class='text'></div>
<div class='score'></div>
</div>
</div>
<div class='ui popup radar-popup'>
<h4 class='title'>Gitee 指数包含如下维度</h4>
<div class='project-radar-list'>
<div class='descript-contianer'>
<div class='descript-title'>
<p>代码活跃度</p>
<p>社区活跃度</p>
<p>团队健康</p>
<p>流行趋势</p>
<p>影响力</p>
</div>
<div class='descript'>
<p>：与代码提交频次相关</p>
<p>：与项目和用户的issue、pr互动相关</p>
<p>：与团队成员人数和稳定度相关</p>
<p>：与项目近期受关注度相关</p>
<p>：与项目的star、下载量等社交指标相关</p>
</div>
</div>
</div>
<div class='finaltime'></div>
</div>
</div>
<script src="https://assets.gitee.com/assets/skill_radar/rep_app-bfe82d2bc79d00c15f1a571f5370c79b.js"></script>

</div>
</div>
<div class='side-item contrib' data-url='/openeuler/docs/contributors_count?ref=stable2-20.03_LTS_SP1' id='contributor'>
<div class='header'>
<h4>
贡献者
<span class='text-muted' id='contributor-count'></span>
</h4>
<a class="ui link button pull-right" href="/openeuler/docs/contributors?ref=stable2-20.03_LTS_SP1">全部</a>
</div>
<div class='content' id='contributor-list'></div>
<div class='ui active centered inline loader' id='contributor-loader'></div>
</div>
<div class='side-item events' data-url='/openeuler/docs/events.json' id='proj-events'>
<div class='header'>
<h4>近期动态</h4>
</div>
<div class='content'>
<div class='ui comments' id='event-list'></div>
<a class="loadmore hide" href="javascript:void(0);">加载更多
<i class='icon dropdown'></i>
</a><center>
<div class='text-muted nomore hide'>不能加载更多了</div>
<div class='ui inline loader active'></div>
</center>
</div>
</div>
</div>
<div class='ui modal tiny' id='edit-project-description'>
<i class='iconfont icon-close close'></i>
<div class='header'>编辑仓库简介</div>
<div class='content'>
<div class='item mb-2'>
<div class='title label'>简介内容</div>
<div class='ui small input'>
<textarea maxlength='200' name='project[description]' placeholder='描述' rows='5'>This is openEuler documentation repository,</textarea>
</div>
</div>
<div class='item mb-2'>
<div class='title label'>主页</div>
<div class='ui small input'>
<input data-regex-value='(^$)|(^(http|https):\/\/(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5]).*)|(^(http|https):\/\/[a-zA-Z0-9]+([_\-\.]{1}[a-zA-Z0-9]+)*\.[a-zA-Z]{2,10}(:[0-9]{1,10})?(\?.*)?(\/.*)?$)' name='project[homepage]' placeholder='主页(eg: https://gitee.com)' type='text' value=''>
</div>
</div>
</div>
<div class='actions'>
<button class='ui button blank cancel'>取消</button>
<button class='ui button orange btn-save'>保存更改</button>
</div>
</div>

<script>
  window.gon.projectRightSide = {
    homepage: "",
    description: "This is openEuler documentation repository,",
    url: '/openeuler/docs/update_description',
    i18n: {
      invalidHomepage: '不是有效的 http 地址',
      descriptionLimitExceeded: '简介长度不得超过%{limit}个字符',
      noDescription: '暂无描述',
      noPermission: '无权限操作！',
      requestError: '修改发生错误，请稍后重试！'
    }
  }
  window.gon.cloneArrSelectedLabel = [] || []
  $(function () {
    var $editModal = $('#edit-project-description')
    $editModal.modal({
      onShow: function () {
        window.globalUtils.getFocus($editModal.find('textarea'))
      }
    })
    $('.project__right-side').on('click', '.header .btn-edit', function () {
      $editModal.modal('show')
    })
    $('#license-popup').popup({ position: 'bottom center', lastResort: 'bottom center' })
  
    $('.js-project-label_show').projectLabel({
      i18n: {
        empty: "标签名不能为空",
        verify: "标签名只允许包含中文、字母、数字或者中划线(-)，不能以中划线开头，且长度少于35个字符",
        max: "最多选择 5 个标签"
      }
    })
  })
</script>

</div>
</div>
</div>
<script>
  (function() {
    $(function() {
      Tree.init();
      return TreeCommentActions.init();
    });
  
  }).call(this);
</script>

</div>
<script>
  (function() {
    var donateModal;
  
    Gitee.modalHelper = new GiteeModalHelper({
      alertText: '提示',
      okText: '确定'
    });
  
    donateModal = new ProjectDonateModal({
      el: '#project-donate-modal',
      alipayUrl: '/openeuler/docs/alipay',
      wepayUrl: '/openeuler/docs/wepay',
      nameIsBlank: '名称不能为空',
      nameTooLong: '名称过长（最多为 36 个字符）',
      modalHelper: Gitee.modalHelper
    });
  
    if (null === 'true') {
      donateModal.show();
    }
  
    $('#project-donate').on('click', function() {
      return donateModal.show();
    });
  
  }).call(this);
</script>
<script>
  Tree.initHighlightTheme('white')
</script>


</div>
<div class='gitee-project-extension'>
<div class='extension public'>1</div>
<div class='extension https'>https://gitee.com/openeuler/docs.git</div>
<div class='extension ssh'>git@gitee.com:openeuler/docs.git</div>
<div class='extension namespace'>openeuler</div>
<div class='extension repo'>docs</div>
<div class='extension name'>docs</div>
<div class='extension branch'>stable2-20.03_LTS_SP1</div>
</div>

<script>
  $(function() {
    GitLab.GfmAutoComplete.dataSource = "/openeuler/docs/autocomplete_sources"
    GitLab.GfmAutoComplete.Emoji.assetBase = '/assets/emoji'
    GitLab.GfmAutoComplete.setup();
  });
</script>

<footer id='git-footer-main'>
<div class='ui container'>
<div class='logo-row'>
<img class='logo-img' src='/static/images/logo-black.svg?t=158106666'>
</div>
<div class='name-important'>
深圳市奥思网络科技有限公司版权所有
</div>
<div class='ui two column grid d-flex-center'>
<div class='nine wide column git-footer-left'>
<div class='ui four column grid' id='footer-left'>
<div class='column'>
<div class='ui link list'>
<div class='item'>
<a class="item" href="/about_us">关于我们</a>
</div>
<div class='item'>
<a class="item" href="https://www.oschina.net/news/131099/oschina-hiring">加入我们</a>
</div>
<div class='item'>
<a class="item" href="/terms">使用条款</a>
</div>
<div class='item'>
<a class="item" href="/oschina/git-osc/issues">意见建议</a>
</div>
<div class='item'>
<a class="item" href="/links.html">合作伙伴</a>
</div>
</div>
</div>
<div class='column'>
<div class='ui link list'>
<div class='item'>
<a class="item" href="/all-about-git">Git 大全</a>
</div>
<div class='item'>
<a class="item" href="https://oschina.gitee.io/learn-git-branching/">Git 命令学习</a>
</div>
<div class='item'>
<a class="item" href="https://copycat.gitee.com/">CopyCat 代码克隆检测</a>
</div>
<div class='item'>
<a class="item" href="/appclient">APP与插件下载</a>
</div>
</div>
</div>
<div class='column'>
<div class='ui link list'>
<div class='item'>
<a class="item" href="/gitee_reward">Gitee Reward</a>
</div>
<div class='item'>
<a class="item" href="/gitee-stars">Gitee 封面人物</a>
</div>
<div class='item'>
<a class="item" href="/gvp">GVP 项目</a>
</div>
<div class='item'>
<a class="item" href="https://blog.gitee.com/">Gitee 博客</a>
</div>
<div class='item'>
<a class="item" href="/enterprises#nonprofit-plan">Gitee 公益计划</a>
</div>
</div>
</div>
<div class='column'>
<div class='ui link list'>
<div class='item'>
<a class="item" href="/api/v5/swagger">OpenAPI</a>
</div>
<div class='item'>
<a class="item" href="/help">帮助文档</a>
</div>
<div class='item'>
<a class="item" href="/self_services">在线自助服务</a>
</div>
<div class='item'>
<a class="item" href="/help/articles/4338#article-header0">更新日志</a>
</div>
</div>
</div>
</div>
</div>
<div class='seven wide column right aligned followus git-footer-right'>
<div class='qrcode mini_app'>
<img src="https://assets.gitee.com/assets/mini_app-e5eee5a21c552b69ae6bf2cf87406b59.jpg" alt="Mini app" />
<p class='mini_app-text'>微信小程序</p>
</div>
<div class='qrcode weixin'>
<img src="https://assets.gitee.com/assets/qrcode-weixin-9e7cfb27165143d2b8e8b268a52ea822.jpg" alt="Qrcode weixin" />
<p class='weixin-text'>微信服务号</p>
</div>
<div class='phone-and-qq column'>
<div class='ui list official-support-container'>
<div class='item'>
<a class="icon-popup" title="点击加入 Gitee 官方群" href="//qm.qq.com/cgi-bin/qm/qr?k=OUfztMuf7jElTIf78lMuNT_D_lZYOWnd"><i class='iconfont icon-logo-qq'></i>
<span>官方技术交流QQ群：515965326</span>
</a></div>
<div class='item mail-and-zhihu'>
<a href="mailto: git@oschina.cn"><i class='iconfont icon-msg-mail'></i>
<span id='git-footer-email'>git#oschina.cn</span>
</a></div>
<div class='item mail-and-zhihu'>
<a target="_blank" href="https://www.zhihu.com/org/ma-yun-osc/"><i class='iconfont icon-zhihu'></i>
<span>Gitee</span>
</a></div>
<div class='item tel'>
<a>
<i class='iconfont icon-tel'></i>
<span>售前及售后使用咨询：400-606-0201</span>
</a>
</div>
</div>
</div>
</div>
</div>
</div>
<div class='bottombar'>
<div class='ui container'>
<div class='ui d-flex d-flex-between'>
<div class='seven wide column partner d-flex'>
<div class='open-atom d-flex-center'>
<img class="logo-openatom mr-1" src="https://assets.gitee.com/assets/logo-openatom-d083391cc8a54e283529f3fc11cc38ca.svg" alt="Logo openatom" />
<a target="_blank" href="https://www.openatom.org/">开放原子开源基金会</a>
<div class='sub-title ml-1'>合作代码托管平台</div>
</div>
<div class='report-12377 d-flex-center ml-3'>
<img class="report-12377__logo mr-1" src="https://assets.gitee.com/assets/12377@2x-1aa42ed2d2256f82a61ecf57be1ec244.png" alt="12377@2x" />
<a target="_blank" href="https://12377.cn">违法和不良信息举报中心</a>
</div>
<div class='copyright ml-3'>
<a href="http://beian.miit.gov.cn/">粤ICP备12009483号</a>
</div>
</div>
<div class='nine wide column right aligned'>
<i class='icon world'></i>
<a href="/language/zh-CN">简 体</a>
/
<a href="/language/zh-TW">繁 體</a>
/
<a href="/language/en">English</a>
</div>
</div>
</div>
</div>
</footer>
<script>
  var officialEmail = $('#git-footer-email').text()
  $('#git-footer-main .icon-popup').popup({ position: 'bottom center' })
  $('#git-footer-email').text(officialEmail.replace('#', '@'))
  window.gon.popover_card_locale = {
    follow:"关注",
    unfollow:"已关注",
    gvp_title: "GVP - Gitee 最有价值开源项目",
    project: "项目",
    org: "开源组织",
    member: "",
    author: "作者",
    user_blocked: "该用户已被屏蔽或已注销",
    net_error: "网络错误",
    unknown_exception: "未知异常"
  }
  window.gon.select_message = {
    placeholder: "请输入个人空间地址或完整的邮箱地址"
  }
</script>
<script src="https://assets.gitee.com/webpacks/popover_card-5e5f80166768e5968f94.bundle.js"></script>


<div class='side-toolbar'>
<div class='button toolbar-help'>
<i class='iconfont icon-help'></i>
</div>
<div class='ui popup left center dark'>点此查找更多帮助</div>
<div class='toolbar-help-dialog'>
<div class='toolbar-dialog-header'>
<h3 class='toolbar-dialog-title'>搜索帮助</h3>
<form class="toolbar-help-search-form" action="/help/load_keywords_data" accept-charset="UTF-8" method="get"><input name="utf8" type="hidden" value="&#x2713;" />
<div class='ui icon input fluid toolbar-help-search'>
<input name='keywords' placeholder='请输入产品名称或问题' type='text'>
<i class='icon search'></i>
</div>
</form>

<i class='iconfont icon-close toolbar-dialog-close-icon'></i>
</div>
<div class='toolbar-dialog-content'>
<div class='toolbar-help-hot-search'>
<div class='toolbar-roll'>
<a class="init active" title="Git 命令在线学习" href="https://oschina.gitee.io/learn-git-branching/?utm_source==gitee-help-widget"><i class='Blue icon icon-command iconfont'></i>
<span>Git 命令在线学习</span>
</a><a class="init " title="如何在 Gitee 导入 GitHub 仓库" href="https://gitee.com/help/articles/4261?utm_source==gitee-help-widget"><i class='icon icon-clipboard iconfont orange'></i>
<span>如何在 Gitee 导入 GitHub 仓库</span>
</a></div>
<div class='toolbar-list'>
<div class='toolbar-list-item'>
<a href="/help/articles/4114">Git 仓库基础操作</a>
</div>
<div class='toolbar-list-item'>
<a href="/help/articles/4166">企业版和社区版功能对比</a>
</div>
<div class='toolbar-list-item'>
<a href="/help/articles/4191">SSH 公钥设置</a>
</div>
<div class='toolbar-list-item'>
<a href="/help/articles/4194">如何处理代码冲突</a>
</div>
<div class='toolbar-list-item'>
<a href="/help/articles/4232">仓库体积过大，如何减小？</a>
</div>
<div class='toolbar-list-item'>
<a href="/help/articles/4279">如何找回被删除的仓库数据</a>
</div>
<div class='toolbar-list-item'>
<a href="/help/articles/4283">Gitee 产品配额说明</a>
</div>
<div class='toolbar-list-item'>
<a href="/help/articles/4284">GitHub仓库快速导入Gitee及同步更新</a>
</div>
<div class='toolbar-list-item'>
<a href="/help/articles/4328">什么是 Release（发行版）</a>
</div>
</div>
</div>
<div class='toolbar-help-search-reseult'>
<div class='toolbar-help-flex-column'>
<div class='ui centered inline loader toolbar-help-loader'></div>
<div class='toolbar-list'></div>
<div class='toolbar-help-link-to-help'>
<a target="_blank" href="">查看更多搜索结果</a>
</div>
</div>
</div>
</div>
</div>
<script>
  var opt = { position: 'left center'};
  var $helpSideToolbar = $('.button.toolbar-help');
  var $toolbarRoll = $('.toolbar-roll');
  
  $(function() {
    if (false) {
      $helpSideToolbar.popup(opt).popup({lastResort:'left center'})
    } else {
      $helpSideToolbar.popup({lastResort:'left center'}).popup('show', opt);
      setTimeout(function() {
        $helpSideToolbar.popup('hide', opt);
      }, 3000);
    }
  
    if ($toolbarRoll.length) {
      setInterval(function() {
        var $nextActiveLink = $toolbarRoll.find('a.active').next();
        if (!$nextActiveLink.length) {
          $nextActiveLink = $toolbarRoll.find('a:first-child');
        }
        $nextActiveLink.attr('class', 'active').siblings().removeClass('active init');
      }, 5000);
    }
  })
</script>

<div class='button share-link'>
<i class='iconfont icon-share'></i>
</div>
<div class='ui popup dark'>
<div class='header'>
分享到
</div>
<div class='bdsharebuttonbox' style='display: flex'>
<a class='iconfont icon-home-service-wechat' data-cmd='weixin' title='分享到微信'></a>
<a class='iconfont icon-weibo' data-cmd='tsina' title='分享到新浪微博'></a>
<a class='iconfont icon-qq' data-cmd='sqq' title='分享到QQ好友'></a>
<a class='iconfont icon-qzone' data-cmd='qzone' title='分享到QQ空间'></a>
</div>
</div>
<div class='popup button' id='home-comment'>
<i class='iconfont icon-comment'></i>
</div>
<div class='ui popup dark'>评论</div>
<div class='toolbar-appeal popup button'>
<i class='iconfont icon-report'></i>
</div>
<div class='ui popup dark'>
仓库举报
</div>
<script>
  $('.toolbar-appeal').popup({ position: 'left center' });
</script>

<div class='button gotop popup' id='gotop'>
<i class='iconfont icon-top'></i>
</div>
<div class='ui popup dark'>回到顶部</div>
</div>
<div class='form modal normal-modal tiny ui' id='unlanding-complaint-modal'>
<i class='iconfont icon-close close'></i>
<div class='header'>
登录提示
</div>
<div class='container actions'>
<div class='content'>
该操作需登录 Gitee 帐号，请先登录后再操作。
</div>
<div class='ui orange icon large button ok'>
立即登录
</div>
<div class='ui button blank cancel'>
没有帐号，去注册
</div>
</div>
</div>
<script>
  var $elm = $('.toolbar-appeal');
  
  $elm.on('click', function() {
    var modals = $("#unlanding-complaint-modal.normal-modal");
    if (modals.length > 1) {
      modals.eq(0).modal('show');
    } else {
      modals.modal('show');
    }
  })
  $("#unlanding-complaint-modal.normal-modal").modal({
    onDeny: function() {
      window.location.href = "/signup?from=";
    },
    onApprove: function() {
      window.location.href = "/login?from=";
    }
  })
</script>

<style>
  .side-toolbar .bdsharebuttonbox a {
    font-size: 24px;
    color: white !important;
    opacity: 0.9;
    margin: 6px 6px 0px 6px;
    background-image: none;
    text-indent: 0;
    height: auto;
    width: auto;
  }
  
  #udesk_btn a{
    margin: 0px 20px 217px 0px !important;
  }
</style>
<script>
  (function() {
    $('#project-user-message').popup({
      position: 'left center'
    });
  
  }).call(this);
</script>
<script>
  Gitee.initSideToolbar({
    hasComment: true,
    commentUrl: '/openeuler/docs#tree_comm_title'
  })
</script>
<script>
  window._bd_share_config = {
    "common": {
      "bdSnsKey": {},
      "bdText": document.title,
      "bdMini": "1",
      "bdMiniList": ["bdxc","tqf","douban","bdhome","sqq","thx","ibaidu","meilishuo","mogujie","diandian","huaban","duitang","hx","fx","youdao","sdo","qingbiji","people","xinhua","mail","isohu","yaolan","wealink","ty","iguba","fbook","twi","linkedin","h163","evernotecn","copy","print"],
      "bdPic": "",
      "bdStyle": "1",
      "bdSize": "32"
    },
    "share": {}
  }
</script>
<script src="/bd_share/static/api/js/share.js"></script>



<style>
  .gitee-stars-main-widget {
    display: none;
    position: fixed;
    left: 0;
    bottom: 0;
    z-index: 106; }
    .gitee-stars-main-widget .close-icon {
      width: 20px;
      right: 10px;
      position: absolute;
      top: 0px;
      cursor: pointer; }
    .gitee-stars-main-widget .people-image {
      width: 200px;
      margin: 0 10px; }
  
  .gitee-stars-main-widget.gitee-stars-widget .close-icon {
    left: 20px; }
</style>
<div class='gitee-stars-main-widget pendan-widget'>
<a target="_blank" href="https://gitee.com/gitee-community/gitee-talk"><img class="people-image" src="https://images.gitee.com/uploads/images/2021/0916/105716_1d94204e_1850385.png" alt="105716 1d94204e 1850385" />
<img class="close-icon" src="https://images.gitee.com/uploads/images/2021/0916/105716_2d26be5c_1850385.png" alt="105716 2d26be5c 1850385" />
</a></div>
<script>
  $(function () {
    var $giteeStarsWidget = $('.gitee-stars-main-widget')
    var cookieKey = "visit-gitee--2021-09-16 11:06:56 +0800"
  
    if ($.cookie(cookieKey) == 1) {
      $giteeStarsWidget.hide()
    } else {
      $giteeStarsWidget.show()
    }
  
    $giteeStarsWidget.on('click', '.close-icon', function (e) {
      e.preventDefault()
      $.cookie(cookieKey, 1, {path: '/', expires: 60})
      $giteeStarsWidget.hide()
    })
  })
</script>


<script>
  (function() {
    this.__gac = {
      domain: 'www.oschina.net'
    };
  
  }).call(this);
</script>

<script src="https://assets.gitee.com/assets/bdstatic/app-070a9e339ac82bf2bf7ef20375cd4121.js"></script>
<script src="https://hm.baidu.com/hm.js?6bc840df1e0b2cbbd5d0aab3e06b2610" async="async"></script>
</body>
</html>
