

<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
  <title>
  eigen / eigen / source &mdash; Bitbucket
</title>
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  <meta name="description" content="" />
  <meta name="keywords" content="" />
  <!--[if lt IE 9]>
  <script src="https://dwz7u9t8u8usb.cloudfront.net/m/e218cff6a4fb/js/lib/html5.js"></script>
  <![endif]-->

  <script>
    (function (window) {
      // prevent stray occurrences of `console.log` from causing errors in IE
      var console = window.console || (window.console = {});
      console.log || (console.log = function () {});

      var BB = window.BB || (window.BB = {});
      BB.debug = false;
      BB.cname = false;
      BB.CANON_URL = 'https://bitbucket.org';
      BB.MEDIA_URL = 'https://dwz7u9t8u8usb.cloudfront.net/m/e218cff6a4fb/';
      BB.images = {
        noAvatar: 'https://dwz7u9t8u8usb.cloudfront.net/m/e218cff6a4fb/img/no_avatar.png'
      };
      BB.user = {"isKbdShortcutsEnabled": true, "isSshEnabled": false};
      BB.user.has = (function () {
        var betaFeatures = [];
        betaFeatures.push('repo2');
        return function (feature) {
          return _.contains(betaFeatures, feature);
        };
      }());
      BB.targetUser = BB.user;
  
      BB.repo || (BB.repo = {});
  
      BB.user.isAdmin = false;
      BB.repo.id = 11837;
    
    
      BB.repo.language = null;
      BB.repo.pygmentsLanguage = null;
    
    
      BB.repo.slug = 'eigen';
    
    
      BB.repo.owner = {
        username: 'eigen'
      };
    
      // Coerce `BB.repo` to a string to get
      // "davidchambers/mango" or whatever.
      BB.repo.toString = function () {
        return BB.cname ? this.slug : this.owner.username + '/' + this.slug;
      }
    
    
      BB.changeset = 'c40708b9088d'
    
    
  
    }(this));
  </script>

  


  <link rel="stylesheet" href="https://dwz7u9t8u8usb.cloudfront.net/m/e218cff6a4fb/bun/css/bundle.css"/>



  <link rel="search" type="application/opensearchdescription+xml" href="/opensearch.xml" title="Bitbucket" />
  <link rel="icon" href="https://dwz7u9t8u8usb.cloudfront.net/m/e218cff6a4fb/img/logo_new.png" type="image/png" />
  <link type="text/plain" rel="author" href="/humans.txt" />


  
    <script src="https://dwz7u9t8u8usb.cloudfront.net/m/e218cff6a4fb/bun/js/bundle.js"></script>
  



</head>

<body id="" class="">
  <script>
    if (navigator.userAgent.indexOf(' AppleWebKit/') === -1) {
      $('body').addClass('non-webkit')
    }
    $('body')
      .addClass($.client.os.toLowerCase())
      .addClass($.client.browser.toLowerCase())
  </script>
  <!--[if IE 8]>
  <script>jQuery(document.body).addClass('ie8')</script>
  <![endif]-->
  <!--[if IE 9]>
  <script>jQuery(document.body).addClass('ie9')</script>
  <![endif]-->

  <div id="wrapper">



  <div id="header-wrap">
    <div id="header">
    <ul id="global-nav">
      <li><a class="home" href="http://www.atlassian.com">Atlassian Home</a></li>
      <li><a class="docs" href="http://confluence.atlassian.com/display/BITBUCKET">Documentation</a></li>
      <li><a class="support" href="/support">Support</a></li>
      <li><a class="blog" href="http://blog.bitbucket.org">Blog</a></li>
      <li><a class="forums" href="http://groups.google.com/group/bitbucket-users">Forums</a></li>
    </ul>
    <a href="/" id="logo">Bitbucket by Atlassian</a>

    <div id="main-nav">
    
      <ul class="clearfix">
        <li><a href="/plans">Pricing &amp; signup</a></li>
        <li><a id="explore-link" href="/explore">Explore Bitbucket</a></li>
        <li><a href="/account/signin/?next=/eigen/eigen/src/c40708b9088d/cmake/FindEigen3.cmake">Log in</a></li>
        

<li class="search-box">
  
    <form action="/repo/all">
      <input type="search" results="5" autosave="bitbucket-explore-search"
             name="name" id="searchbox"
             placeholder="owner/repo" />
  
  </form>
</li>

      </ul>
    
    </div>

  

    </div>
  </div>

    <div id="header-messages">
  
  
    
    
    
    
  

    
   </div>



    <div id="content">
      <div id="source">
      
  
  





  <script>
    jQuery(function ($) {
        var cookie = $.cookie,
            cookieOptions, date,
            $content = $('#content'),
            $pane = $('#what-is-bitbucket'),
            $hide = $pane.find('[href="#hide"]').css('display', 'block').hide();

        date = new Date();
        date.setTime(date.getTime() + 365 * 24 * 60 * 60 * 1000);
        cookieOptions = { path: '/', expires: date };

        if (cookie('toggle_status') == 'hide') $content.addClass('repo-desc-hidden');

        $('#toggle-repo-content').click(function (event) {
            event.preventDefault();
            $content.toggleClass('repo-desc-hidden');
            cookie('toggle_status', cookie('toggle_status') == 'show' ? 'hide' : 'show', cookieOptions);
        });

        if (!cookie('hide_intro_message')) $pane.show();

        $hide.click(function (event) {
            event.preventDefault();
            cookie('hide_intro_message', true, cookieOptions);
            $pane.slideUp('slow');
        });

        $pane.hover(
            function () { $hide.fadeIn('fast'); },
            function () { $hide.fadeOut('fast'); });

      (function () {
        // Update "recently-viewed-repos" cookie for
        // the "repositories" drop-down.
        var
          id = BB.repo.id,
          cookieName = 'recently-viewed-repos_' + BB.user.id,
          rvr = cookie(cookieName),
          ids = rvr? rvr.split(','): [],
          idx = _.indexOf(ids, '' + id);

        // Remove `id` from `ids` if present.
        if (~idx) ids.splice(idx, 1);

        cookie(
          cookieName,
          // Insert `id` as the first item, then call
          // `join` on the resulting array to produce
          // something like "114694,27542,89002,84570".
          [id].concat(ids.slice(0, 4)).join(),
          {path: '/', expires: 1e6} // "never" expires
        );
      }());
    });
  </script>



  
  
  
  
  
    <div id="what-is-bitbucket" class="new-to-bitbucket">
      <h2>eigen <span id="slogan">is sharing code with you</span></h2>
      <img src="https://secure.gravatar.com/avatar/c6e4f955c65d1cb805dc10b546292b6e?d=identicon&s=32" alt="" class="avatar" />
      <p>Bitbucket is a code hosting site. Unlimited public and private repositories. Free for small teams.</p>
      <div class="primary-action-link signup"><a href="/account/signup/?utm_source=internal&utm_medium=banner&utm_campaign=what_is_bitbucket">Try Bitbucket free</a></div>
      <a href="#hide" title="Don't show this again">Don't show this again</a>
    </div>
  


<div id="tabs" class="tabs">
  <ul>
    <li>
      <a href="/eigen/eigen/overview" id="repo-overview-link">Overview</a>
    </li>

    <li>
      <a href="/eigen/eigen/downloads" id="repo-downloads-link">Downloads (<span id="downloads-count">0</span>)</a>
    </li>

    

    <li>
      <a href="/eigen/eigen/pull-requests" id="repo-pr-link">Pull requests (0)</a>
    </li>

    <li class="selected">
      
        <a href="/eigen/eigen/src" id="repo-source-link">Source</a>
      
    </li>

    <li>
      <a href="/eigen/eigen/changesets" id="repo-commits-link">Commits</a>
    </li>

    <li id="wiki-tab" class="dropdown"
      style="display:
                        none  
        
      ">
      <a href="/eigen/eigen/wiki" id="repo-wiki-link">Wiki</a>
    </li>

    <li id="issues-tab" class="dropdown inertial-hover"
      style="display:
                      none  
        
      ">
      <a href="/eigen/eigen/issues?status=new&amp;status=open" id="repo-issues-link">Issues (24) &raquo;</a>
      <ul>
        <li><a href="/eigen/eigen/issues/new">Create new issue</a></li>
        <li><a href="/eigen/eigen/issues?status=new">New issues</a></li>
        <li><a href="/eigen/eigen/issues?status=new&amp;status=open">Open issues</a></li>
        <li><a href="/eigen/eigen/issues?status=duplicate&amp;status=invalid&amp;status=resolved&amp;status=wontfix">Closed issues</a></li>
        
        <li><a href="/eigen/eigen/issues">All issues</a></li>
        <li><a href="/eigen/eigen/issues/query">Advanced query</a></li>
      </ul>
    </li>

    
  </ul>

  <ul>
    <li>
      <a href="/eigen/eigen/descendants" id="repo-forks-link">Forks/queues (33)</a>
    </li>

    <li>
      <a href="/eigen/eigen/zealots">Followers (<span id="followers-count">93</span>)</a>
    </li>
  </ul>
</div>



 

  <div class="repo-menu" id="repo-menu">
    <ul id="repo-menu-links">
    
      <li>
        <a href="/eigen/eigen/rss" class="rss" title="RSS feed for eigen">RSS</a>
      </li>

      <li><a id="repo-fork-link" href="/eigen/eigen/fork" class="fork">fork</a></li>
      
        
          <li><a id="repo-patch-queue-link" href="/eigen/eigen/hack" class="patch-queue">patch queue</a></li>
        
      
      <li>
        <a id="repo-follow-link" rel="nofollow" href="/eigen/eigen/follow" class="follow">follow</a>
      </li>
      
          
      
      
        <li class="get-source inertial-hover">
          <a class="source">get source</a>
          <ul class="downloads">
            
              
              <li><a rel="nofollow" href="/eigen/eigen/get/c40708b9088d.zip">zip</a></li>
              <li><a rel="nofollow" href="/eigen/eigen/get/c40708b9088d.tar.gz">gz</a></li>
              <li><a rel="nofollow" href="/eigen/eigen/get/c40708b9088d.tar.bz2">bz2</a></li>
            
          </ul>
        </li>
      
    </ul>

  
    <ul class="metadata">
      
      
        <li class="branches inertial-hover">branches
          <ul>
            <li><a href="/eigen/eigen/src/0b4add5ae3db" title="2.0">2.0</a>
              
              
              <a rel="nofollow" class="menu-compare"
                 href="/eigen/eigen/compare/2.0..default"
                 title="Show changes between 2.0 and the main branch.">compare</a>
              
            </li>
            <li><a href="/eigen/eigen/src/5aa2890d724b" title="3.0">3.0</a>
              
              
              <a rel="nofollow" class="menu-compare"
                 href="/eigen/eigen/compare/3.0..default"
                 title="Show changes between 3.0 and the main branch.">compare</a>
              
            </li>
            <li><a href="/eigen/eigen/src/da4d86c25a8d" title="default">default</a>
              
              
            </li>
          </ul>
        </li>
      
      
      <li class="tags inertial-hover">tags
        <ul>
          <li><a href="/eigen/eigen/src/5aa2890d724b">tip</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..tip"
                 title="Show changes between tip and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/6e7488e20373">3.0.5</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..3.0.5"
                 title="Show changes between 3.0.5 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/304c88ca3aff">3.1.0-alpha2</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..3.1.0-alpha2"
                 title="Show changes between 3.1.0-alpha2 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/a810d5dbab47">3.1.0-alpha1</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..3.1.0-alpha1"
                 title="Show changes between 3.1.0-alpha1 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/b23437e61a07">2.0.17</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..2.0.17"
                 title="Show changes between 2.0.17 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/13a11181fc5a">3.0.4</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..3.0.4"
                 title="Show changes between 3.0.4 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/063c73f683ed">3.0.3</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..3.0.3"
                 title="Show changes between 3.0.3 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/786d67eaed28">3.0.2</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..3.0.2"
                 title="Show changes between 3.0.2 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/599fc4f7c736">3.0.1</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..3.0.1"
                 title="Show changes between 3.0.1 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/9ca09dbd70ce">2.0.16</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..2.0.16"
                 title="Show changes between 2.0.16 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/65ee2328342f">3.0.0</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..3.0.0"
                 title="Show changes between 3.0.0 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/b6456624eae7">3.0-rc1</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..3.0-rc1"
                 title="Show changes between 3.0-rc1 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/c40708b9088d">3.0-beta4</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..3.0-beta4"
                 title="Show changes between 3.0-beta4 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/7ae24ca6f389">3.0-beta3</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..3.0-beta3"
                 title="Show changes between 3.0-beta3 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/5c4180ad827b">3.0-beta2</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..3.0-beta2"
                 title="Show changes between 3.0-beta2 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/0938af7840b0">2.0.15</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..2.0.15"
                 title="Show changes between 2.0.15 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/12a658962d4e">3.0-beta1</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..3.0-beta1"
                 title="Show changes between 3.0-beta1 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/f30db88dec8b">2.0.14</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..2.0.14"
                 title="Show changes between 2.0.14 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/99d564175944">2.0.13</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..2.0.13"
                 title="Show changes between 2.0.13 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/a1b04d0da20b">2.0.12</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..2.0.12"
                 title="Show changes between 2.0.12 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/e5330af419bb">2.0.11</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..2.0.11"
                 title="Show changes between 2.0.11 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/b28443d6f3a1">2.0.10</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..2.0.10"
                 title="Show changes between 2.0.10 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/52718cf6633a">2.0.9</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..2.0.9"
                 title="Show changes between 2.0.9 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/869be801ed89">2.0.8</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..2.0.8"
                 title="Show changes between 2.0.8 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/2b628fd1756e">2.0.7</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..2.0.7"
                 title="Show changes between 2.0.7 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/831410e91175">2.0.6</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..2.0.6"
                 title="Show changes between 2.0.6 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/76e6e7fb5312">2.0.5</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..2.0.5"
                 title="Show changes between 2.0.5 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/fc59f8734ffd">2.0.4</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..2.0.4"
                 title="Show changes between 2.0.4 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/c4564054e151">2.0.3</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..2.0.3"
                 title="Show changes between 2.0.3 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/d72c9170451f">2.0.2</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..2.0.2"
                 title="Show changes between 2.0.2 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/d49097c25d80">after-hg-migration</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..after-hg-migration"
                 title="Show changes between after-hg-migration and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/e17630a40408">before-hg-migration</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..before-hg-migration"
                 title="Show changes between before-hg-migration and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/7d14ad088ac2">2.0.1</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..2.0.1"
                 title="Show changes between 2.0.1 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/eda654d4cda2">2.0.0</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..2.0.0"
                 title="Show changes between 2.0.0 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/3b8120f07786">2.0-rc1</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..2.0-rc1"
                 title="Show changes between 2.0-rc1 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/b9d48561579f">2.0-beta6</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..2.0-beta6"
                 title="Show changes between 2.0-beta6 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/19dfc0e7666b">2.0-beta5</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..2.0-beta5"
                 title="Show changes between 2.0-beta5 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/7a7d8a9526f0">2.0-beta4</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..2.0-beta4"
                 title="Show changes between 2.0-beta4 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/2db9468678c6">2.0-beta3</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..2.0-beta3"
                 title="Show changes between 2.0-beta3 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/ee9a7c468a9e">2.0-beta2</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..2.0-beta2"
                 title="Show changes between 2.0-beta2 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/375224817dce">2.0-beta1</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..2.0-beta1"
                 title="Show changes between 2.0-beta1 and the main branch.">compare</a>
            </li>
          <li><a href="/eigen/eigen/src/655348878731">actual-start-from-scratch</a>
            
            
              <a rel="nofollow" class='menu-compare'
                 href="/eigen/eigen/compare/..actual-start-from-scratch"
                 title="Show changes between actual-start-from-scratch and the main branch.">compare</a>
            </li>
        </ul>
      </li>
     
     
    </ul>
  
</div>

<div class="repo-menu" id="repo-desc">
    <ul id="repo-menu-links-mini">
      

      
      <li>
        <a href="/eigen/eigen/rss" class="rss" title="RSS feed for eigen"></a>
      </li>

      <li><a href="/eigen/eigen/fork" class="fork" title="Fork"></a></li>
      
        
          <li><a href="/eigen/eigen/hack" class="patch-queue" title="Patch queue"></a></li>
        
      
      <li>
        <a rel="nofollow" href="/eigen/eigen/follow" class="follow">follow</a>
      </li>
      
          
      
      
        <li>
          <a class="source" title="Get source"></a>
          <ul class="downloads">
            
              
              <li><a rel="nofollow" href="/eigen/eigen/get/c40708b9088d.zip">zip</a></li>
              <li><a rel="nofollow" href="/eigen/eigen/get/c40708b9088d.tar.gz">gz</a></li>
              <li><a rel="nofollow" href="/eigen/eigen/get/c40708b9088d.tar.bz2">bz2</a></li>
            
          </ul>
        </li>
      
    </ul>

    <h3 id="repo-heading" class="public hg">
      <a class="owner-username" href="/eigen">eigen</a> /
      <a class="repo-name" href="/eigen/eigen">eigen</a>
    
      <span><a href="http://eigen.tuxfamily.org/">http://eigen.tuxfamily.org/</a></span>
    

    
    </h3>

    
      <p class="repo-desc-description">Eigen is a C++ template library for linear algebra: vectors, matrices, and related algorithms. It is versatile, fast, elegant and works on many platforms (OS/Compilers).</p>
    

  <div id="repo-desc-cloneinfo">Clone this repository (size: 26.4 MB):
    <a href="https://bitbucket.org/eigen/eigen" class="https">HTTPS</a> /
    <a href="ssh://hg@bitbucket.org/eigen/eigen" class="ssh">SSH</a>
    <pre id="clone-url-https">hg clone https://bitbucket.org/eigen/eigen</pre>
    <pre id="clone-url-ssh">hg clone ssh://hg@bitbucket.org/eigen/eigen</pre>
    
      <img src="https://bitbucket-assetroot.s3.amazonaws.com/c/photos/2009/Aug/17/Eigen_Silly_Professor_35x35_avatar.png" class="repo-avatar" />
    
  </div>

        <a href="#" id="toggle-repo-content"></a>

        

</div>




      
  <div id="source-container">
    

  <div id="source-path">
    <h1>
      <a href="/eigen/eigen/src" class="src-pjax">eigen</a> /

  
    
      <a href="/eigen/eigen/src/c40708b9088d/cmake/" class="src-pjax">cmake</a> /
    
  

  
    
      <span>FindEigen3.cmake</span>
    
  

    </h1>
  </div>

  <div class="labels labels-csv">
  
    <dl>
  
    
      <dt>Tag</dt>
      
        <dd class="tag unabridged"><a href="/eigen/eigen/changesets/tip/..tag(%223.0-beta4%22)" title="3.0-beta4">3.0-beta4</a></dd>
      
    
  
  
    
  
  
</dl>

  
  </div>


  
  <div id="source-view">
    <div class="header">
      <ul class="metadata">
        <li><code>c40708b9088d</code></li>
        
          
            <li>81 loc</li>
          
        
        <li>2.9 KB</li>
      </ul>
      <ul class="source-view-links">
        
        <li><a id="embed-link" href="https://bitbucket.org/eigen/eigen/src/c40708b9088d/cmake/FindEigen3.cmake?embed=t">embed</a></li>
        
        <li><a href="/eigen/eigen/history/cmake/FindEigen3.cmake">history</a></li>
        
        <li><a href="/eigen/eigen/annotate/c40708b9088d/cmake/FindEigen3.cmake">annotate</a></li>
        
        <li><a href="/eigen/eigen/raw/c40708b9088d/cmake/FindEigen3.cmake">raw</a></li>
        <li>
          <form action="/eigen/eigen/diff/cmake/FindEigen3.cmake" class="source-view-form">
          
            <input type="hidden" name="diff2" value="a91c15a82934" />
            <select name="diff1">
            
              
                <option value="a91c15a82934">a91c15a82934</option>
              
            
              
                <option value="e70d7f3b2bdd">e70d7f3b2bdd</option>
              
            
              
                <option value="2cc8587775da">2cc8587775da</option>
              
            
              
                <option value="ff31a88f14cc">ff31a88f14cc</option>
              
            
              
                <option value="66f4fe4f00bf">66f4fe4f00bf</option>
              
            
            </select>
            <input type="submit" value="diff" />
          
          </form>
        </li>
      </ul>
    </div>
  
    <div>
    <table class="highlighttable"><tr><td class="linenos"><div class="linenodiv"><pre><a href="#cl-1"> 1</a>
<a href="#cl-2"> 2</a>
<a href="#cl-3"> 3</a>
<a href="#cl-4"> 4</a>
<a href="#cl-5"> 5</a>
<a href="#cl-6"> 6</a>
<a href="#cl-7"> 7</a>
<a href="#cl-8"> 8</a>
<a href="#cl-9"> 9</a>
<a href="#cl-10">10</a>
<a href="#cl-11">11</a>
<a href="#cl-12">12</a>
<a href="#cl-13">13</a>
<a href="#cl-14">14</a>
<a href="#cl-15">15</a>
<a href="#cl-16">16</a>
<a href="#cl-17">17</a>
<a href="#cl-18">18</a>
<a href="#cl-19">19</a>
<a href="#cl-20">20</a>
<a href="#cl-21">21</a>
<a href="#cl-22">22</a>
<a href="#cl-23">23</a>
<a href="#cl-24">24</a>
<a href="#cl-25">25</a>
<a href="#cl-26">26</a>
<a href="#cl-27">27</a>
<a href="#cl-28">28</a>
<a href="#cl-29">29</a>
<a href="#cl-30">30</a>
<a href="#cl-31">31</a>
<a href="#cl-32">32</a>
<a href="#cl-33">33</a>
<a href="#cl-34">34</a>
<a href="#cl-35">35</a>
<a href="#cl-36">36</a>
<a href="#cl-37">37</a>
<a href="#cl-38">38</a>
<a href="#cl-39">39</a>
<a href="#cl-40">40</a>
<a href="#cl-41">41</a>
<a href="#cl-42">42</a>
<a href="#cl-43">43</a>
<a href="#cl-44">44</a>
<a href="#cl-45">45</a>
<a href="#cl-46">46</a>
<a href="#cl-47">47</a>
<a href="#cl-48">48</a>
<a href="#cl-49">49</a>
<a href="#cl-50">50</a>
<a href="#cl-51">51</a>
<a href="#cl-52">52</a>
<a href="#cl-53">53</a>
<a href="#cl-54">54</a>
<a href="#cl-55">55</a>
<a href="#cl-56">56</a>
<a href="#cl-57">57</a>
<a href="#cl-58">58</a>
<a href="#cl-59">59</a>
<a href="#cl-60">60</a>
<a href="#cl-61">61</a>
<a href="#cl-62">62</a>
<a href="#cl-63">63</a>
<a href="#cl-64">64</a>
<a href="#cl-65">65</a>
<a href="#cl-66">66</a>
<a href="#cl-67">67</a>
<a href="#cl-68">68</a>
<a href="#cl-69">69</a>
<a href="#cl-70">70</a>
<a href="#cl-71">71</a>
<a href="#cl-72">72</a>
<a href="#cl-73">73</a>
<a href="#cl-74">74</a>
<a href="#cl-75">75</a>
<a href="#cl-76">76</a>
<a href="#cl-77">77</a>
<a href="#cl-78">78</a>
<a href="#cl-79">79</a>
<a href="#cl-80">80</a>
</pre></div></td><td class="code"><div class="highlight"><pre><a name="cl-1"></a><span class="c"># - Try to find Eigen3 lib</span>
<a name="cl-2"></a><span class="err">#</span>
<a name="cl-3"></a><span class="c"># This module supports requiring a minimum version, e.g. you can do</span>
<a name="cl-4"></a><span class="c">#   find_package(Eigen3 3.1.2)</span>
<a name="cl-5"></a><span class="c"># to require version 3.1.2 or newer of Eigen3.</span>
<a name="cl-6"></a><span class="err">#</span>
<a name="cl-7"></a><span class="c"># Once done this will define</span>
<a name="cl-8"></a><span class="err">#</span>
<a name="cl-9"></a><span class="c">#  EIGEN3_FOUND - system has eigen lib with correct version</span>
<a name="cl-10"></a><span class="c">#  EIGEN3_INCLUDE_DIR - the eigen include directory</span>
<a name="cl-11"></a><span class="c">#  EIGEN3_VERSION - eigen version</span>
<a name="cl-12"></a>
<a name="cl-13"></a><span class="c"># Copyright (c) 2006, 2007 Montel Laurent, &lt;montel@kde.org&gt;</span>
<a name="cl-14"></a><span class="c"># Copyright (c) 2008, 2009 Gael Guennebaud, &lt;g.gael@free.fr&gt;</span>
<a name="cl-15"></a><span class="c"># Copyright (c) 2009 Benoit Jacob &lt;jacob.benoit.1@gmail.com&gt;</span>
<a name="cl-16"></a><span class="c"># Redistribution and use is allowed according to the terms of the 2-clause BSD license.</span>
<a name="cl-17"></a>
<a name="cl-18"></a><span class="nb">if</span><span class="p">(</span><span class="s">NOT</span> <span class="s">Eigen3_FIND_VERSION</span><span class="p">)</span>
<a name="cl-19"></a>  <span class="nb">if</span><span class="p">(</span><span class="s">NOT</span> <span class="s">Eigen3_FIND_VERSION_MAJOR</span><span class="p">)</span>
<a name="cl-20"></a>    <span class="nb">set</span><span class="p">(</span><span class="s">Eigen3_FIND_VERSION_MAJOR</span> <span class="s">2</span><span class="p">)</span>
<a name="cl-21"></a>  <span class="nb">endif</span><span class="p">(</span><span class="s">NOT</span> <span class="s">Eigen3_FIND_VERSION_MAJOR</span><span class="p">)</span>
<a name="cl-22"></a>  <span class="nb">if</span><span class="p">(</span><span class="s">NOT</span> <span class="s">Eigen3_FIND_VERSION_MINOR</span><span class="p">)</span>
<a name="cl-23"></a>    <span class="nb">set</span><span class="p">(</span><span class="s">Eigen3_FIND_VERSION_MINOR</span> <span class="s">91</span><span class="p">)</span>
<a name="cl-24"></a>  <span class="nb">endif</span><span class="p">(</span><span class="s">NOT</span> <span class="s">Eigen3_FIND_VERSION_MINOR</span><span class="p">)</span>
<a name="cl-25"></a>  <span class="nb">if</span><span class="p">(</span><span class="s">NOT</span> <span class="s">Eigen3_FIND_VERSION_PATCH</span><span class="p">)</span>
<a name="cl-26"></a>    <span class="nb">set</span><span class="p">(</span><span class="s">Eigen3_FIND_VERSION_PATCH</span> <span class="s">0</span><span class="p">)</span>
<a name="cl-27"></a>  <span class="nb">endif</span><span class="p">(</span><span class="s">NOT</span> <span class="s">Eigen3_FIND_VERSION_PATCH</span><span class="p">)</span>
<a name="cl-28"></a>
<a name="cl-29"></a>  <span class="nb">set</span><span class="p">(</span><span class="s">Eigen3_FIND_VERSION</span> <span class="s2">&quot;${Eigen3_FIND_VERSION_MAJOR}.${Eigen3_FIND_VERSION_MINOR}.${Eigen3_FIND_VERSION_PATCH}&quot;</span><span class="p">)</span>
<a name="cl-30"></a><span class="nb">endif</span><span class="p">(</span><span class="s">NOT</span> <span class="s">Eigen3_FIND_VERSION</span><span class="p">)</span>
<a name="cl-31"></a>
<a name="cl-32"></a><span class="nb">macro</span><span class="p">(</span><span class="s">_eigen3_check_version</span><span class="p">)</span>
<a name="cl-33"></a>  <span class="nb">file</span><span class="p">(</span><span class="s">READ</span> <span class="s2">&quot;${EIGEN3_INCLUDE_DIR}/Eigen/src/Core/util/Macros.h&quot;</span> <span class="s">_eigen3_version_header</span><span class="p">)</span>
<a name="cl-34"></a>
<a name="cl-35"></a>  <span class="nb">string</span><span class="p">(</span><span class="s">REGEX</span> <span class="s">MATCH</span> <span class="s2">&quot;define[ \t]+EIGEN_WORLD_VERSION[ \t]+([0-9]+)&quot;</span> <span class="s">_eigen3_world_version_match</span> <span class="s2">&quot;${_eigen3_version_header}&quot;</span><span class="p">)</span>
<a name="cl-36"></a>  <span class="nb">set</span><span class="p">(</span><span class="s">EIGEN3_WORLD_VERSION</span> <span class="s2">&quot;${CMAKE_MATCH_1}&quot;</span><span class="p">)</span>
<a name="cl-37"></a>  <span class="nb">string</span><span class="p">(</span><span class="s">REGEX</span> <span class="s">MATCH</span> <span class="s2">&quot;define[ \t]+EIGEN_MAJOR_VERSION[ \t]+([0-9]+)&quot;</span> <span class="s">_eigen3_major_version_match</span> <span class="s2">&quot;${_eigen3_version_header}&quot;</span><span class="p">)</span>
<a name="cl-38"></a>  <span class="nb">set</span><span class="p">(</span><span class="s">EIGEN3_MAJOR_VERSION</span> <span class="s2">&quot;${CMAKE_MATCH_1}&quot;</span><span class="p">)</span>
<a name="cl-39"></a>  <span class="nb">string</span><span class="p">(</span><span class="s">REGEX</span> <span class="s">MATCH</span> <span class="s2">&quot;define[ \t]+EIGEN_MINOR_VERSION[ \t]+([0-9]+)&quot;</span> <span class="s">_eigen3_minor_version_match</span> <span class="s2">&quot;${_eigen3_version_header}&quot;</span><span class="p">)</span>
<a name="cl-40"></a>  <span class="nb">set</span><span class="p">(</span><span class="s">EIGEN3_MINOR_VERSION</span> <span class="s2">&quot;${CMAKE_MATCH_1}&quot;</span><span class="p">)</span>
<a name="cl-41"></a>
<a name="cl-42"></a>  <span class="nb">set</span><span class="p">(</span><span class="s">EIGEN3_VERSION</span> <span class="o">${</span><span class="nv">EIGEN3_WORLD_VERSION</span><span class="o">}</span><span class="s">.</span><span class="o">${</span><span class="nv">EIGEN3_MAJOR_VERSION</span><span class="o">}</span><span class="s">.</span><span class="o">${</span><span class="nv">EIGEN3_MINOR_VERSION</span><span class="o">}</span><span class="p">)</span>
<a name="cl-43"></a>  <span class="nb">if</span><span class="p">(</span><span class="o">${</span><span class="nv">EIGEN3_VERSION</span><span class="o">}</span> <span class="s">VERSION_LESS</span> <span class="o">${</span><span class="nv">Eigen3_FIND_VERSION</span><span class="o">}</span><span class="p">)</span>
<a name="cl-44"></a>    <span class="nb">set</span><span class="p">(</span><span class="s">EIGEN3_VERSION_OK</span> <span class="s">FALSE</span><span class="p">)</span>
<a name="cl-45"></a>  <span class="nb">else</span><span class="p">(</span><span class="o">${</span><span class="nv">EIGEN3_VERSION</span><span class="o">}</span> <span class="s">VERSION_LESS</span> <span class="o">${</span><span class="nv">Eigen3_FIND_VERSION</span><span class="o">}</span><span class="p">)</span>
<a name="cl-46"></a>    <span class="nb">set</span><span class="p">(</span><span class="s">EIGEN3_VERSION_OK</span> <span class="s">TRUE</span><span class="p">)</span>
<a name="cl-47"></a>  <span class="nb">endif</span><span class="p">(</span><span class="o">${</span><span class="nv">EIGEN3_VERSION</span><span class="o">}</span> <span class="s">VERSION_LESS</span> <span class="o">${</span><span class="nv">Eigen3_FIND_VERSION</span><span class="o">}</span><span class="p">)</span>
<a name="cl-48"></a>
<a name="cl-49"></a>  <span class="nb">if</span><span class="p">(</span><span class="s">NOT</span> <span class="s">EIGEN3_VERSION_OK</span><span class="p">)</span>
<a name="cl-50"></a>
<a name="cl-51"></a>    <span class="nb">message</span><span class="p">(</span><span class="s">STATUS</span> <span class="s2">&quot;Eigen3 version ${EIGEN3_VERSION} found in ${EIGEN3_INCLUDE_DIR}, &quot;</span>
<a name="cl-52"></a>                   <span class="s2">&quot;but at least version ${Eigen3_FIND_VERSION} is required&quot;</span><span class="p">)</span>
<a name="cl-53"></a>  <span class="nb">endif</span><span class="p">(</span><span class="s">NOT</span> <span class="s">EIGEN3_VERSION_OK</span><span class="p">)</span>
<a name="cl-54"></a><span class="nb">endmacro</span><span class="p">(</span><span class="s">_eigen3_check_version</span><span class="p">)</span>
<a name="cl-55"></a>
<a name="cl-56"></a><span class="nb">if</span> <span class="p">(</span><span class="s">EIGEN3_INCLUDE_DIR</span><span class="p">)</span>
<a name="cl-57"></a>
<a name="cl-58"></a>  <span class="c"># in cache already</span>
<a name="cl-59"></a>  <span class="err">_eigen3_check_version()</span>
<a name="cl-60"></a>  <span class="nb">set</span><span class="p">(</span><span class="s">EIGEN3_FOUND</span> <span class="o">${</span><span class="nv">EIGEN3_VERSION_OK</span><span class="o">}</span><span class="p">)</span>
<a name="cl-61"></a>
<a name="cl-62"></a><span class="nb">else</span> <span class="p">(</span><span class="s">EIGEN3_INCLUDE_DIR</span><span class="p">)</span>
<a name="cl-63"></a>
<a name="cl-64"></a>  <span class="nb">find_path</span><span class="p">(</span><span class="s">EIGEN3_INCLUDE_DIR</span> <span class="s">NAMES</span> <span class="s">signature_of_eigen3_matrix_library</span>
<a name="cl-65"></a>      <span class="s">PATHS</span>
<a name="cl-66"></a>      <span class="o">${</span><span class="nv">CMAKE_INSTALL_PREFIX</span><span class="o">}</span><span class="s">/include</span>
<a name="cl-67"></a>      <span class="o">${</span><span class="nv">KDE4_INCLUDE_DIR</span><span class="o">}</span>
<a name="cl-68"></a>      <span class="s">PATH_SUFFIXES</span> <span class="s">eigen3</span> <span class="s">eigen</span>
<a name="cl-69"></a>    <span class="p">)</span>
<a name="cl-70"></a>
<a name="cl-71"></a>  <span class="nb">if</span><span class="p">(</span><span class="s">EIGEN3_INCLUDE_DIR</span><span class="p">)</span>
<a name="cl-72"></a>    <span class="err">_eigen3_check_version()</span>
<a name="cl-73"></a>  <span class="nb">endif</span><span class="p">(</span><span class="s">EIGEN3_INCLUDE_DIR</span><span class="p">)</span>
<a name="cl-74"></a>
<a name="cl-75"></a>  <span class="nb">include</span><span class="p">(</span><span class="s">FindPackageHandleStandardArgs</span><span class="p">)</span>
<a name="cl-76"></a>  <span class="nb">find_package_handle_standard_args</span><span class="p">(</span><span class="s">Eigen3</span> <span class="s">DEFAULT_MSG</span> <span class="s">EIGEN3_INCLUDE_DIR</span> <span class="s">EIGEN3_VERSION_OK</span><span class="p">)</span>
<a name="cl-77"></a>
<a name="cl-78"></a>  <span class="nb">mark_as_advanced</span><span class="p">(</span><span class="s">EIGEN3_INCLUDE_DIR</span><span class="p">)</span>
<a name="cl-79"></a>
<a name="cl-80"></a><span class="nb">endif</span><span class="p">(</span><span class="s">EIGEN3_INCLUDE_DIR</span><span class="p">)</span>
</pre></div>
</td></tr></table>
    </div>
  
  </div>
  


  <div id="mask"><div></div></div>

  </div>

      </div>
    </div>

  </div>

  <div id="footer">
    <ul id="footer-nav">
      <li>Copyright © 2012 <a href="http://atlassian.com">Atlassian</a></li>
      <li><a href="http://www.atlassian.com/hosted/terms.jsp">Terms of Service</a></li>
      <li><a href="http://www.atlassian.com/about/privacy.jsp">Privacy</a></li>
      <li><a href="//bitbucket.org/site/master/issues/new">Report a Bug to Bitbucket</a></li>
      <li><a href="http://confluence.atlassian.com/x/IYBGDQ">API</a></li>
      <li><a href="http://status.bitbucket.org/">Server Status</a></li>
    </ul>
    <ul id="social-nav">
      <li class="blog"><a href="http://blog.bitbucket.org">Bitbucket Blog</a></li>
      <li class="twitter"><a href="http://www.twitter.com/bitbucket">Twitter</a></li>
    </ul>
    <h5>We run</h5>
    <ul id="technologies">
      <li><a href="http://www.djangoproject.com/">Django 1.3.1</a></li>
      <li><a href="//bitbucket.org/jespern/django-piston/">Piston 0.3dev</a></li>
      <li><a href="http://git-scm.com/">Git 1.7.6</a></li>
      <li><a href="http://www.selenic.com/mercurial/">Hg 1.9.1</a></li>
      <li><a href="http://www.python.org">Python 2.7.2</a></li>
      <li>d0e63b086281 | bitbucket15</li>
    </ul>
  </div>

  <script src="https://dwz7u9t8u8usb.cloudfront.net/m/e218cff6a4fb/js/lib/global.js"></script>






  <script>
    BB.gaqPush(['_trackPageview']);
  
    BB.gaqPush(['atl._trackPageview']);

    

    

    (function () {
        var ga = document.createElement('script');
        ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
        ga.setAttribute('async', 'true');
        document.documentElement.firstChild.appendChild(ga);
    }());
  </script>

</body>
</html>
