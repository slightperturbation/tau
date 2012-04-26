

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
        <li><a href="/account/signin/?next=/eigen/eigen/src/c40708b9088d/cmake/FindGSL.cmake">Log in</a></li>
        

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
    
  

  
    
      <span>FindGSL.cmake</span>
    
  

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
        
          
            <li>170 loc</li>
          
        
        <li>4.9 KB</li>
      </ul>
      <ul class="source-view-links">
        
        <li><a id="embed-link" href="https://bitbucket.org/eigen/eigen/src/c40708b9088d/cmake/FindGSL.cmake?embed=t">embed</a></li>
        
        <li><a href="/eigen/eigen/history/cmake/FindGSL.cmake">history</a></li>
        
        <li><a href="/eigen/eigen/annotate/c40708b9088d/cmake/FindGSL.cmake">annotate</a></li>
        
        <li><a href="/eigen/eigen/raw/c40708b9088d/cmake/FindGSL.cmake">raw</a></li>
        <li>
          <form action="/eigen/eigen/diff/cmake/FindGSL.cmake" class="source-view-form">
          
            <input type="hidden" name="diff2" value="ad9a41c1d32a" />
            <select name="diff1">
            
              
                <option value="ad9a41c1d32a">ad9a41c1d32a</option>
              
            
              
                <option value="88c50cd078dd">88c50cd078dd</option>
              
            
              
                <option value="9db16f0cda5a">9db16f0cda5a</option>
              
            
              
                <option value="32c4ad657438">32c4ad657438</option>
              
            
            </select>
            <input type="submit" value="diff" />
          
          </form>
        </li>
      </ul>
    </div>
  
    <div>
    <table class="highlighttable"><tr><td class="linenos"><div class="linenodiv"><pre><a href="#cl-1">  1</a>
<a href="#cl-2">  2</a>
<a href="#cl-3">  3</a>
<a href="#cl-4">  4</a>
<a href="#cl-5">  5</a>
<a href="#cl-6">  6</a>
<a href="#cl-7">  7</a>
<a href="#cl-8">  8</a>
<a href="#cl-9">  9</a>
<a href="#cl-10"> 10</a>
<a href="#cl-11"> 11</a>
<a href="#cl-12"> 12</a>
<a href="#cl-13"> 13</a>
<a href="#cl-14"> 14</a>
<a href="#cl-15"> 15</a>
<a href="#cl-16"> 16</a>
<a href="#cl-17"> 17</a>
<a href="#cl-18"> 18</a>
<a href="#cl-19"> 19</a>
<a href="#cl-20"> 20</a>
<a href="#cl-21"> 21</a>
<a href="#cl-22"> 22</a>
<a href="#cl-23"> 23</a>
<a href="#cl-24"> 24</a>
<a href="#cl-25"> 25</a>
<a href="#cl-26"> 26</a>
<a href="#cl-27"> 27</a>
<a href="#cl-28"> 28</a>
<a href="#cl-29"> 29</a>
<a href="#cl-30"> 30</a>
<a href="#cl-31"> 31</a>
<a href="#cl-32"> 32</a>
<a href="#cl-33"> 33</a>
<a href="#cl-34"> 34</a>
<a href="#cl-35"> 35</a>
<a href="#cl-36"> 36</a>
<a href="#cl-37"> 37</a>
<a href="#cl-38"> 38</a>
<a href="#cl-39"> 39</a>
<a href="#cl-40"> 40</a>
<a href="#cl-41"> 41</a>
<a href="#cl-42"> 42</a>
<a href="#cl-43"> 43</a>
<a href="#cl-44"> 44</a>
<a href="#cl-45"> 45</a>
<a href="#cl-46"> 46</a>
<a href="#cl-47"> 47</a>
<a href="#cl-48"> 48</a>
<a href="#cl-49"> 49</a>
<a href="#cl-50"> 50</a>
<a href="#cl-51"> 51</a>
<a href="#cl-52"> 52</a>
<a href="#cl-53"> 53</a>
<a href="#cl-54"> 54</a>
<a href="#cl-55"> 55</a>
<a href="#cl-56"> 56</a>
<a href="#cl-57"> 57</a>
<a href="#cl-58"> 58</a>
<a href="#cl-59"> 59</a>
<a href="#cl-60"> 60</a>
<a href="#cl-61"> 61</a>
<a href="#cl-62"> 62</a>
<a href="#cl-63"> 63</a>
<a href="#cl-64"> 64</a>
<a href="#cl-65"> 65</a>
<a href="#cl-66"> 66</a>
<a href="#cl-67"> 67</a>
<a href="#cl-68"> 68</a>
<a href="#cl-69"> 69</a>
<a href="#cl-70"> 70</a>
<a href="#cl-71"> 71</a>
<a href="#cl-72"> 72</a>
<a href="#cl-73"> 73</a>
<a href="#cl-74"> 74</a>
<a href="#cl-75"> 75</a>
<a href="#cl-76"> 76</a>
<a href="#cl-77"> 77</a>
<a href="#cl-78"> 78</a>
<a href="#cl-79"> 79</a>
<a href="#cl-80"> 80</a>
<a href="#cl-81"> 81</a>
<a href="#cl-82"> 82</a>
<a href="#cl-83"> 83</a>
<a href="#cl-84"> 84</a>
<a href="#cl-85"> 85</a>
<a href="#cl-86"> 86</a>
<a href="#cl-87"> 87</a>
<a href="#cl-88"> 88</a>
<a href="#cl-89"> 89</a>
<a href="#cl-90"> 90</a>
<a href="#cl-91"> 91</a>
<a href="#cl-92"> 92</a>
<a href="#cl-93"> 93</a>
<a href="#cl-94"> 94</a>
<a href="#cl-95"> 95</a>
<a href="#cl-96"> 96</a>
<a href="#cl-97"> 97</a>
<a href="#cl-98"> 98</a>
<a href="#cl-99"> 99</a>
<a href="#cl-100">100</a>
<a href="#cl-101">101</a>
<a href="#cl-102">102</a>
<a href="#cl-103">103</a>
<a href="#cl-104">104</a>
<a href="#cl-105">105</a>
<a href="#cl-106">106</a>
<a href="#cl-107">107</a>
<a href="#cl-108">108</a>
<a href="#cl-109">109</a>
<a href="#cl-110">110</a>
<a href="#cl-111">111</a>
<a href="#cl-112">112</a>
<a href="#cl-113">113</a>
<a href="#cl-114">114</a>
<a href="#cl-115">115</a>
<a href="#cl-116">116</a>
<a href="#cl-117">117</a>
<a href="#cl-118">118</a>
<a href="#cl-119">119</a>
<a href="#cl-120">120</a>
<a href="#cl-121">121</a>
<a href="#cl-122">122</a>
<a href="#cl-123">123</a>
<a href="#cl-124">124</a>
<a href="#cl-125">125</a>
<a href="#cl-126">126</a>
<a href="#cl-127">127</a>
<a href="#cl-128">128</a>
<a href="#cl-129">129</a>
<a href="#cl-130">130</a>
<a href="#cl-131">131</a>
<a href="#cl-132">132</a>
<a href="#cl-133">133</a>
<a href="#cl-134">134</a>
<a href="#cl-135">135</a>
<a href="#cl-136">136</a>
<a href="#cl-137">137</a>
<a href="#cl-138">138</a>
<a href="#cl-139">139</a>
<a href="#cl-140">140</a>
<a href="#cl-141">141</a>
<a href="#cl-142">142</a>
<a href="#cl-143">143</a>
<a href="#cl-144">144</a>
<a href="#cl-145">145</a>
<a href="#cl-146">146</a>
<a href="#cl-147">147</a>
<a href="#cl-148">148</a>
<a href="#cl-149">149</a>
<a href="#cl-150">150</a>
<a href="#cl-151">151</a>
<a href="#cl-152">152</a>
<a href="#cl-153">153</a>
<a href="#cl-154">154</a>
<a href="#cl-155">155</a>
<a href="#cl-156">156</a>
<a href="#cl-157">157</a>
<a href="#cl-158">158</a>
<a href="#cl-159">159</a>
<a href="#cl-160">160</a>
<a href="#cl-161">161</a>
<a href="#cl-162">162</a>
<a href="#cl-163">163</a>
<a href="#cl-164">164</a>
<a href="#cl-165">165</a>
<a href="#cl-166">166</a>
<a href="#cl-167">167</a>
<a href="#cl-168">168</a>
<a href="#cl-169">169</a>
<a href="#cl-170">170</a>
</pre></div></td><td class="code"><div class="highlight"><pre><a name="cl-1"></a><span class="c"># Try to find gnu scientific library GSL</span>
<a name="cl-2"></a><span class="c"># See </span>
<a name="cl-3"></a><span class="c"># http://www.gnu.org/software/gsl/  and</span>
<a name="cl-4"></a><span class="c"># http://gnuwin32.sourceforge.net/packages/gsl.htm</span>
<a name="cl-5"></a><span class="err">#</span>
<a name="cl-6"></a><span class="c"># Once run this will define: </span>
<a name="cl-7"></a><span class="c"># </span>
<a name="cl-8"></a><span class="c"># GSL_FOUND       = system has GSL lib</span>
<a name="cl-9"></a><span class="err">#</span>
<a name="cl-10"></a><span class="c"># GSL_LIBRARIES   = full path to the libraries</span>
<a name="cl-11"></a><span class="c">#    on Unix/Linux with additional linker flags from &quot;gsl-config --libs&quot;</span>
<a name="cl-12"></a><span class="c"># </span>
<a name="cl-13"></a><span class="c"># CMAKE_GSL_CXX_FLAGS  = Unix compiler flags for GSL, essentially &quot;`gsl-config --cxxflags`&quot;</span>
<a name="cl-14"></a><span class="err">#</span>
<a name="cl-15"></a><span class="c"># GSL_INCLUDE_DIR      = where to find headers </span>
<a name="cl-16"></a><span class="err">#</span>
<a name="cl-17"></a><span class="c"># GSL_LINK_DIRECTORIES = link directories, useful for rpath on Unix</span>
<a name="cl-18"></a><span class="c"># GSL_EXE_LINKER_FLAGS = rpath on Unix</span>
<a name="cl-19"></a><span class="err">#</span>
<a name="cl-20"></a><span class="c"># Felix Woelk 07/2004</span>
<a name="cl-21"></a><span class="c"># Jan Woetzel</span>
<a name="cl-22"></a><span class="err">#</span>
<a name="cl-23"></a><span class="c"># www.mip.informatik.uni-kiel.de</span>
<a name="cl-24"></a><span class="c"># --------------------------------</span>
<a name="cl-25"></a>
<a name="cl-26"></a><span class="nb">IF</span><span class="p">(</span><span class="s">WIN32</span><span class="p">)</span>
<a name="cl-27"></a>  <span class="c"># JW tested with gsl-1.8, Windows XP, MSVS 7.1</span>
<a name="cl-28"></a>  <span class="nb">SET</span><span class="p">(</span><span class="s">GSL_POSSIBLE_ROOT_DIRS</span>
<a name="cl-29"></a>    <span class="o">${</span><span class="nv">GSL_ROOT_DIR</span><span class="o">}</span>
<a name="cl-30"></a>    <span class="err">$</span><span class="s">ENV{GSL_ROOT_DIR}</span>
<a name="cl-31"></a>    <span class="o">${</span><span class="nv">GSL_DIR</span><span class="o">}</span>
<a name="cl-32"></a>    <span class="o">${</span><span class="nv">GSL_HOME</span><span class="o">}</span>    
<a name="cl-33"></a>    <span class="err">$</span><span class="s">ENV{GSL_DIR}</span>
<a name="cl-34"></a>    <span class="err">$</span><span class="s">ENV{GSL_HOME}</span>
<a name="cl-35"></a>    <span class="err">$</span><span class="s">ENV{EXTRA}</span>
<a name="cl-36"></a>    <span class="s2">&quot;C:/Program Files/GnuWin32&quot;</span>
<a name="cl-37"></a>    <span class="p">)</span>
<a name="cl-38"></a>  <span class="nb">FIND_PATH</span><span class="p">(</span><span class="s">GSL_INCLUDE_DIR</span>
<a name="cl-39"></a>    <span class="s">NAMES</span> <span class="s">gsl/gsl_cdf.h</span> <span class="s">gsl/gsl_randist.h</span>
<a name="cl-40"></a>    <span class="s">PATHS</span> <span class="o">${</span><span class="nv">GSL_POSSIBLE_ROOT_DIRS</span><span class="o">}</span>
<a name="cl-41"></a>    <span class="s">PATH_SUFFIXES</span> <span class="s">include</span>
<a name="cl-42"></a>    <span class="s">DOC</span> <span class="s2">&quot;GSL header include dir&quot;</span>
<a name="cl-43"></a>    <span class="p">)</span>
<a name="cl-44"></a>  
<a name="cl-45"></a>  <span class="nb">FIND_LIBRARY</span><span class="p">(</span><span class="s">GSL_GSL_LIBRARY</span>
<a name="cl-46"></a>    <span class="s">NAMES</span> <span class="s">libgsl.dll.a</span> <span class="s">gsl</span> <span class="s">libgsl</span>
<a name="cl-47"></a>    <span class="s">PATHS</span>  <span class="o">${</span><span class="nv">GSL_POSSIBLE_ROOT_DIRS</span><span class="o">}</span>
<a name="cl-48"></a>    <span class="s">PATH_SUFFIXES</span> <span class="s">lib</span>
<a name="cl-49"></a>    <span class="s">DOC</span> <span class="s2">&quot;GSL library&quot;</span> <span class="p">)</span>
<a name="cl-50"></a>  
<a name="cl-51"></a>  <span class="nb">if</span><span class="p">(</span><span class="s">NOT</span> <span class="s">GSL_GSL_LIBRARY</span><span class="p">)</span>
<a name="cl-52"></a>  <span class="nb">FIND_FILE</span><span class="p">(</span><span class="s">GSL_GSL_LIBRARY</span>
<a name="cl-53"></a>    <span class="s">NAMES</span> <span class="s">libgsl.dll.a</span>
<a name="cl-54"></a>    <span class="s">PATHS</span>  <span class="o">${</span><span class="nv">GSL_POSSIBLE_ROOT_DIRS</span><span class="o">}</span>
<a name="cl-55"></a>    <span class="s">PATH_SUFFIXES</span> <span class="s">lib</span>
<a name="cl-56"></a>    <span class="s">DOC</span> <span class="s2">&quot;GSL library&quot;</span><span class="p">)</span>
<a name="cl-57"></a>  <span class="nb">endif</span><span class="p">(</span><span class="s">NOT</span> <span class="s">GSL_GSL_LIBRARY</span><span class="p">)</span>
<a name="cl-58"></a>  
<a name="cl-59"></a>  <span class="nb">FIND_LIBRARY</span><span class="p">(</span><span class="s">GSL_GSLCBLAS_LIBRARY</span>
<a name="cl-60"></a>    <span class="s">NAMES</span> <span class="s">libgslcblas.dll.a</span> <span class="s">gslcblas</span> <span class="s">libgslcblas</span>
<a name="cl-61"></a>    <span class="s">PATHS</span>  <span class="o">${</span><span class="nv">GSL_POSSIBLE_ROOT_DIRS</span><span class="o">}</span>
<a name="cl-62"></a>    <span class="s">PATH_SUFFIXES</span> <span class="s">lib</span>
<a name="cl-63"></a>    <span class="s">DOC</span> <span class="s2">&quot;GSL cblas library dir&quot;</span> <span class="p">)</span>
<a name="cl-64"></a>  
<a name="cl-65"></a>  <span class="nb">if</span><span class="p">(</span><span class="s">NOT</span> <span class="s">GSL_GSLCBLAS_LIBRARY</span><span class="p">)</span>
<a name="cl-66"></a>  <span class="nb">FIND_FILE</span><span class="p">(</span><span class="s">GSL_GSLCBLAS_LIBRARY</span>
<a name="cl-67"></a>    <span class="s">NAMES</span> <span class="s">libgslcblas.dll.a</span>
<a name="cl-68"></a>    <span class="s">PATHS</span>  <span class="o">${</span><span class="nv">GSL_POSSIBLE_ROOT_DIRS</span><span class="o">}</span>
<a name="cl-69"></a>    <span class="s">PATH_SUFFIXES</span> <span class="s">lib</span>
<a name="cl-70"></a>    <span class="s">DOC</span> <span class="s2">&quot;GSL library&quot;</span><span class="p">)</span>
<a name="cl-71"></a>  <span class="nb">endif</span><span class="p">(</span><span class="s">NOT</span> <span class="s">GSL_GSLCBLAS_LIBRARY</span><span class="p">)</span>
<a name="cl-72"></a>  
<a name="cl-73"></a>  <span class="nb">SET</span><span class="p">(</span><span class="s">GSL_LIBRARIES</span> <span class="o">${</span><span class="nv">GSL_GSL_LIBRARY</span><span class="o">}</span><span class="p">)</span>
<a name="cl-74"></a>
<a name="cl-75"></a>  <span class="c">#MESSAGE(&quot;DBG\n&quot;</span>
<a name="cl-76"></a>  <span class="c">#  &quot;GSL_GSL_LIBRARY=${GSL_GSL_LIBRARY}\n&quot;</span>
<a name="cl-77"></a>  <span class="c">#  &quot;GSL_GSLCBLAS_LIBRARY=${GSL_GSLCBLAS_LIBRARY}\n&quot;</span>
<a name="cl-78"></a>  <span class="c">#  &quot;GSL_LIBRARIES=${GSL_LIBRARIES}&quot;)</span>
<a name="cl-79"></a>
<a name="cl-80"></a>
<a name="cl-81"></a><span class="nb">ELSE</span><span class="p">(</span><span class="s">WIN32</span><span class="p">)</span>
<a name="cl-82"></a>  
<a name="cl-83"></a>  <span class="nb">IF</span><span class="p">(</span><span class="s">UNIX</span><span class="p">)</span> 
<a name="cl-84"></a>    <span class="nb">SET</span><span class="p">(</span><span class="s">GSL_CONFIG_PREFER_PATH</span> 
<a name="cl-85"></a>      <span class="s2">&quot;$ENV{GSL_DIR}/bin&quot;</span>
<a name="cl-86"></a>      <span class="s2">&quot;$ENV{GSL_DIR}&quot;</span>
<a name="cl-87"></a>      <span class="s2">&quot;$ENV{GSL_HOME}/bin&quot;</span> 
<a name="cl-88"></a>      <span class="s2">&quot;$ENV{GSL_HOME}&quot;</span> 
<a name="cl-89"></a>      <span class="s">CACHE</span> <span class="s">STRING</span> <span class="s2">&quot;preferred path to GSL (gsl-config)&quot;</span><span class="p">)</span>
<a name="cl-90"></a>    <span class="nb">FIND_PROGRAM</span><span class="p">(</span><span class="s">GSL_CONFIG</span> <span class="s">gsl-config</span>
<a name="cl-91"></a>      <span class="o">${</span><span class="nv">GSL_CONFIG_PREFER_PATH</span><span class="o">}</span>
<a name="cl-92"></a>      <span class="s">/usr/bin/</span>
<a name="cl-93"></a>      <span class="p">)</span>
<a name="cl-94"></a>    <span class="c"># MESSAGE(&quot;DBG GSL_CONFIG ${GSL_CONFIG}&quot;)</span>
<a name="cl-95"></a>    
<a name="cl-96"></a>    <span class="nb">IF</span> <span class="p">(</span><span class="s">GSL_CONFIG</span><span class="p">)</span> 
<a name="cl-97"></a>      <span class="c"># set CXXFLAGS to be fed into CXX_FLAGS by the user:</span>
<a name="cl-98"></a>      <span class="nb">SET</span><span class="p">(</span><span class="s">GSL_CXX_FLAGS</span> <span class="s2">&quot;`${GSL_CONFIG} --cflags`&quot;</span><span class="p">)</span>
<a name="cl-99"></a>      
<a name="cl-100"></a>      <span class="c"># set INCLUDE_DIRS to prefix+include</span>
<a name="cl-101"></a>      <span class="nb">EXEC_PROGRAM</span><span class="p">(</span><span class="o">${</span><span class="nv">GSL_CONFIG</span><span class="o">}</span>
<a name="cl-102"></a>        <span class="s">ARGS</span> <span class="s">--prefix</span>
<a name="cl-103"></a>        <span class="s">OUTPUT_VARIABLE</span> <span class="s">GSL_PREFIX</span><span class="p">)</span>
<a name="cl-104"></a>      <span class="nb">SET</span><span class="p">(</span><span class="s">GSL_INCLUDE_DIR</span> <span class="o">${</span><span class="nv">GSL_PREFIX</span><span class="o">}</span><span class="s">/include</span> <span class="s">CACHE</span> <span class="s">STRING</span> <span class="s">INTERNAL</span><span class="p">)</span>
<a name="cl-105"></a>
<a name="cl-106"></a>      <span class="c"># set link libraries and link flags</span>
<a name="cl-107"></a>      <span class="c">#SET(GSL_LIBRARIES &quot;`${GSL_CONFIG} --libs`&quot;)</span>
<a name="cl-108"></a>      <span class="nb">EXEC_PROGRAM</span><span class="p">(</span><span class="o">${</span><span class="nv">GSL_CONFIG</span><span class="o">}</span>
<a name="cl-109"></a>        <span class="s">ARGS</span> <span class="s">--libs</span>
<a name="cl-110"></a>        <span class="s">OUTPUT_VARIABLE</span> <span class="s">GSL_LIBRARIES</span> <span class="p">)</span>
<a name="cl-111"></a>        
<a name="cl-112"></a>      <span class="c"># extract link dirs for rpath  </span>
<a name="cl-113"></a>      <span class="nb">EXEC_PROGRAM</span><span class="p">(</span><span class="o">${</span><span class="nv">GSL_CONFIG</span><span class="o">}</span>
<a name="cl-114"></a>        <span class="s">ARGS</span> <span class="s">--libs</span>
<a name="cl-115"></a>        <span class="s">OUTPUT_VARIABLE</span> <span class="s">GSL_CONFIG_LIBS</span> <span class="p">)</span>
<a name="cl-116"></a>      
<a name="cl-117"></a>      <span class="c"># extract version</span>
<a name="cl-118"></a>      <span class="nb">EXEC_PROGRAM</span><span class="p">(</span><span class="o">${</span><span class="nv">GSL_CONFIG</span><span class="o">}</span>
<a name="cl-119"></a>        <span class="s">ARGS</span> <span class="s">--version</span>
<a name="cl-120"></a>        <span class="s">OUTPUT_VARIABLE</span> <span class="s">GSL_FULL_VERSION</span> <span class="p">)</span>
<a name="cl-121"></a>      
<a name="cl-122"></a>      <span class="c"># split version as major/minor</span>
<a name="cl-123"></a>      <span class="nb">STRING</span><span class="p">(</span><span class="s">REGEX</span> <span class="s">MATCH</span> <span class="s2">&quot;(.)\\..*&quot;</span> <span class="s">GSL_VERSION_MAJOR_</span> <span class="s2">&quot;${GSL_FULL_VERSION}&quot;</span><span class="p">)</span>
<a name="cl-124"></a>      <span class="nb">SET</span><span class="p">(</span><span class="s">GSL_VERSION_MAJOR</span> <span class="o">${</span><span class="nv">CMAKE_MATCH_1</span><span class="o">}</span><span class="p">)</span>
<a name="cl-125"></a>      <span class="nb">STRING</span><span class="p">(</span><span class="s">REGEX</span> <span class="s">MATCH</span> <span class="s2">&quot;.\\.(.*)&quot;</span> <span class="s">GSL_VERSION_MINOR_</span> <span class="s2">&quot;${GSL_FULL_VERSION}&quot;</span><span class="p">)</span>
<a name="cl-126"></a>      <span class="nb">SET</span><span class="p">(</span><span class="s">GSL_VERSION_MINOR</span> <span class="o">${</span><span class="nv">CMAKE_MATCH_1</span><span class="o">}</span><span class="p">)</span>
<a name="cl-127"></a>
<a name="cl-128"></a>      <span class="c"># split off the link dirs (for rpath)</span>
<a name="cl-129"></a>      <span class="c"># use regular expression to match wildcard equivalent &quot;-L*&lt;endchar&gt;&quot;</span>
<a name="cl-130"></a>      <span class="c"># with &lt;endchar&gt; is a space or a semicolon</span>
<a name="cl-131"></a>      <span class="nb">STRING</span><span class="p">(</span><span class="s">REGEX</span> <span class="s">MATCHALL</span> <span class="s2">&quot;[-][L]([^ ;])+&quot;</span> 
<a name="cl-132"></a>        <span class="s">GSL_LINK_DIRECTORIES_WITH_PREFIX</span> 
<a name="cl-133"></a>        <span class="s2">&quot;${GSL_CONFIG_LIBS}&quot;</span> <span class="p">)</span>
<a name="cl-134"></a>      <span class="c">#      MESSAGE(&quot;DBG  GSL_LINK_DIRECTORIES_WITH_PREFIX=${GSL_LINK_DIRECTORIES_WITH_PREFIX}&quot;)</span>
<a name="cl-135"></a>
<a name="cl-136"></a>      <span class="c"># remove prefix -L because we need the pure directory for LINK_DIRECTORIES</span>
<a name="cl-137"></a>      
<a name="cl-138"></a>      <span class="nb">IF</span> <span class="p">(</span><span class="s">GSL_LINK_DIRECTORIES_WITH_PREFIX</span><span class="p">)</span>
<a name="cl-139"></a>        <span class="nb">STRING</span><span class="p">(</span><span class="s">REGEX</span> <span class="s">REPLACE</span> <span class="s2">&quot;[-][L]&quot;</span> <span class="s2">&quot;&quot;</span> <span class="s">GSL_LINK_DIRECTORIES</span> <span class="o">${</span><span class="nv">GSL_LINK_DIRECTORIES_WITH_PREFIX</span><span class="o">}</span> <span class="p">)</span>
<a name="cl-140"></a>      <span class="nb">ENDIF</span> <span class="p">(</span><span class="s">GSL_LINK_DIRECTORIES_WITH_PREFIX</span><span class="p">)</span>
<a name="cl-141"></a>      <span class="nb">SET</span><span class="p">(</span><span class="s">GSL_EXE_LINKER_FLAGS</span> <span class="s2">&quot;-Wl,-rpath,${GSL_LINK_DIRECTORIES}&quot;</span> <span class="s">CACHE</span> <span class="s">STRING</span> <span class="s">INTERNAL</span><span class="p">)</span>
<a name="cl-142"></a>      <span class="c">#      MESSAGE(&quot;DBG  GSL_LINK_DIRECTORIES=${GSL_LINK_DIRECTORIES}&quot;)</span>
<a name="cl-143"></a>      <span class="c">#      MESSAGE(&quot;DBG  GSL_EXE_LINKER_FLAGS=${GSL_EXE_LINKER_FLAGS}&quot;)</span>
<a name="cl-144"></a>
<a name="cl-145"></a>      <span class="c">#      ADD_DEFINITIONS(&quot;-DHAVE_GSL&quot;)</span>
<a name="cl-146"></a>      <span class="c">#      SET(GSL_DEFINITIONS &quot;-DHAVE_GSL&quot;)</span>
<a name="cl-147"></a>      <span class="nb">MARK_AS_ADVANCED</span><span class="p">(</span>
<a name="cl-148"></a>        <span class="s">GSL_CXX_FLAGS</span>
<a name="cl-149"></a>        <span class="s">GSL_INCLUDE_DIR</span>
<a name="cl-150"></a>        <span class="s">GSL_LIBRARIES</span>
<a name="cl-151"></a>        <span class="s">GSL_LINK_DIRECTORIES</span>
<a name="cl-152"></a>        <span class="s">GSL_DEFINITIONS</span>
<a name="cl-153"></a>        <span class="p">)</span>
<a name="cl-154"></a>      <span class="nb">MESSAGE</span><span class="p">(</span><span class="s">STATUS</span> <span class="s2">&quot;Using GSL from ${GSL_PREFIX}&quot;</span><span class="p">)</span>
<a name="cl-155"></a>      
<a name="cl-156"></a>    <span class="nb">ELSE</span><span class="p">(</span><span class="s">GSL_CONFIG</span><span class="p">)</span>
<a name="cl-157"></a>      <span class="nb">MESSAGE</span><span class="p">(</span><span class="s2">&quot;FindGSL.cmake: gsl-config not found. Please set it manually. GSL_CONFIG=${GSL_CONFIG}&quot;</span><span class="p">)</span>
<a name="cl-158"></a>    <span class="nb">ENDIF</span><span class="p">(</span><span class="s">GSL_CONFIG</span><span class="p">)</span>
<a name="cl-159"></a>
<a name="cl-160"></a>  <span class="nb">ENDIF</span><span class="p">(</span><span class="s">UNIX</span><span class="p">)</span>
<a name="cl-161"></a><span class="nb">ENDIF</span><span class="p">(</span><span class="s">WIN32</span><span class="p">)</span>
<a name="cl-162"></a>
<a name="cl-163"></a>
<a name="cl-164"></a><span class="nb">IF</span><span class="p">(</span><span class="s">GSL_LIBRARIES</span><span class="p">)</span>
<a name="cl-165"></a>  <span class="nb">IF</span><span class="p">(</span><span class="s">GSL_INCLUDE_DIR</span> <span class="s">OR</span> <span class="s">GSL_CXX_FLAGS</span><span class="p">)</span>
<a name="cl-166"></a>
<a name="cl-167"></a>    <span class="nb">SET</span><span class="p">(</span><span class="s">GSL_FOUND</span> <span class="s">1</span><span class="p">)</span>
<a name="cl-168"></a>    
<a name="cl-169"></a>  <span class="nb">ENDIF</span><span class="p">(</span><span class="s">GSL_INCLUDE_DIR</span> <span class="s">OR</span> <span class="s">GSL_CXX_FLAGS</span><span class="p">)</span>
<a name="cl-170"></a><span class="nb">ENDIF</span><span class="p">(</span><span class="s">GSL_LIBRARIES</span><span class="p">)</span>
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
      <li>d0e63b086281 | bitbucket05</li>
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
